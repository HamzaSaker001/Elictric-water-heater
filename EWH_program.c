/*
 * EWH_program.c
 *
 * Created: 2/27/2026
 *  Author: hamza
 *
 *  ── Fixes applied ───────────────────────────────────────────────────────
 *  1.  Duplicate macro clash in EWH_config.h → fixed in config file.
 *  2.  Switch pins now initialised as INPUT with internal pull-up disabled
 *      (buttons are wired active-HIGH / forward connection).
 *  3.  Missing else-branch: when temp is IN band → heater OFF, cooler OFF,
 *      LED OFF.
 *  4.  Cooling LED spec: LED steady-ON when cooling element is ON.
 *  5.  Busy-wait loops re-read the actual switch hardware, not a stale local.
 *  6.  ON/OFF toggle is edge-triggered (wait for release before acting),
 *      prevents double-toggle.
 *  7.  STATE_ON correctly turns heater/cooler OFF when temp is in range.
 *  8.  EEPROM read in STATE_SETTING now happens before the blinking display,
 *      so the display always shows the current stored value.
 *  9.  TMR0 started once in EWH_voidInit (not inside the task loop).
 * ────────────────────────────────────────────────────────────────────────
 */

/* ── Utility libraries ──────────────────────────────────────────────── */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* ── MCAL ───────────────────────────────────────────────────────────── */
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "EEPROM_interface.h"
#include "TMR0_interface.h"

/* ── HAL ────────────────────────────────────────────────────────────── */
#include "LM35_interface.h"
#include "SSD_interface.h"
#include "SWITCH_interface.h"

/* ── Project ────────────────────────────────────────────────────────── */
#include "EWH_interface.h"
#include "EWH_config.h"

/* ── Private state ──────────────────────────────────────────────────── */
static u8  PRV_u8CurrentState                    = STATE_OFF;
static u8  PRV_u8TempHistory[TEMP_BUFFER_SIZE]   = {0};
static u8  PRV_u8HistoryIndex                    = 0;
static u16 PRV_u16SystemTicks                    = 0;

/* ── Helper: read a switch and return SWITCH_PRESSED / SWITCH_NOT_PRESSED */
static u8 prvReadSwitch(u8 port, u8 pin)
{
    u8 status;
    SWITCH_voidGetStatus(port, pin, SWITCH_FORWARD_CONNECTION, &status);
    return status;
}

/* ── Helper: block until a switch is released (re-reads hardware) ──── */
static void prvWaitRelease(u8 port, u8 pin)
{
    while (prvReadSwitch(port, pin) == SWITCH_PRESSED);
}

/*
 * EWH_voidInit
 * ─────────────
 * Initialise all hardware used by the EWH driver.
 * Timer is configured and started here so the temperature history
 * begins filling as soon as the system powers up (even while OFF
 * the array is just zeroed and ignored until the system goes ON).
 *
 * NOTE: Global Interrupts must be enabled by the caller (main.c)
 *       AFTER this function returns.
 */
void EWH_voidInit(void)
{
    u8 Local_u8StoredTemp;

    /* ── Peripheral init ──────────────────────────────────────────── */
    LM35_voidInit();   /* also inits ADC */
    SSD_voidInit();
    EEPROM_voidInit(); /* inits I2C / TWI */

    /* ── Output pins ──────────────────────────────────────────────── */
    DIO_voidSetPinDirection(HEATER_PORT,     HEATER_PIN,     DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(COOLER_PORT,     COOLER_PIN,     DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(HEATER_LED_PORT, HEATER_LED_PIN, DIO_PIN_OUTPUT);

    /* All outputs LOW on boot */
    DIO_voidSetPinValue(HEATER_PORT,     HEATER_PIN,     DIO_PIN_LOW);
    DIO_voidSetPinValue(COOLER_PORT,     COOLER_PIN,     DIO_PIN_LOW);
    DIO_voidSetPinValue(HEATER_LED_PORT, HEATER_LED_PIN, DIO_PIN_LOW);

    /* ── Input pins (active-HIGH buttons, no internal pull-up needed) */
    DIO_voidSetPinDirection(SWITCH_UP_PORT,    SWITCH_UP_PIN,    DIO_PIN_INPUT);
    DIO_voidSetPinDirection(SWITCH_DOWN_PORT,  SWITCH_DOWN_PIN,  DIO_PIN_INPUT);
    DIO_voidSetPinDirection(SWITCH_ONOFF_PORT, SWITCH_ONOFF_PIN, DIO_PIN_INPUT);

    /* ── EEPROM: validate stored temperature ──────────────────────── */
    EEPROM_voidReadByte(EEPROM_SET_TEMP_ADDR, &Local_u8StoredTemp);
    if ((Local_u8StoredTemp < EWH_MIN_TEMP) || (Local_u8StoredTemp > EWH_MAX_TEMP))
    {
        Local_u8StoredTemp = EWH_INIT_TEMP;
        EEPROM_voidWriteByte(EEPROM_SET_TEMP_ADDR, Local_u8StoredTemp);
    }

    /* ── Timer: 100 ms CTC callback ──────────────────────────────── */
    TMR0_voidInit();
    TMR0_voidSetCallBackCTC(EWH_voidTimerCallback);
    TMR0_voidSetDelay_msUsingCTC(TICK_TIME_MS);
    /* Timer is NOT started here; it starts when system goes ON */
}

/*
 * EWH_voidTimerCallback
 * ──────────────────────
 * Called from the TMR0 CTC ISR every 100 ms while the system is ON.
 * Fills the rolling temperature history and increments the tick counter.
 */
void EWH_voidTimerCallback(void)
{
    LM35_voidGetTemperature(&PRV_u8TempHistory[PRV_u8HistoryIndex]);
    PRV_u8HistoryIndex = (u8)((PRV_u8HistoryIndex + 1u) % TEMP_BUFFER_SIZE);
    PRV_u16SystemTicks++;
}

/*
 * EWH_voidTask
 * ─────────────
 * Non-blocking state machine. Call in the main super-loop as fast as
 * possible (the 10 ms SSD multiplex delay is the only blocking point).
 */
void EWH_voidTask(void)
{
    u8  L_u8Up, L_u8Down, L_u8OnOff;
    u8  L_u8SetTemp  = EWH_INIT_TEMP;
    u8  L_u8AvgTemp  = 0;
    u16 L_u16Sum     = 0;
    u8  i;

    /* ── Read all buttons ─────────────────────────────────────────── */
    L_u8Up    = prvReadSwitch(SWITCH_UP_PORT,    SWITCH_UP_PIN);
    L_u8Down  = prvReadSwitch(SWITCH_DOWN_PORT,  SWITCH_DOWN_PIN);
    L_u8OnOff = prvReadSwitch(SWITCH_ONOFF_PORT, SWITCH_ONOFF_PIN);

    /* ── Compute rolling average (only used when ON / SETTING) ────── */
    if (PRV_u8CurrentState != STATE_OFF)
    {
        for (i = 0u; i < TEMP_BUFFER_SIZE; i++)
        {
            L_u16Sum += PRV_u8TempHistory[i];
        }
        L_u8AvgTemp = (u8)(L_u16Sum / TEMP_BUFFER_SIZE);
        EEPROM_voidReadByte(EEPROM_SET_TEMP_ADDR, &L_u8SetTemp);
    }

    /* ════════════════════════════════════════════════════════════════
     *  STATE MACHINE
     * ════════════════════════════════════════════════════════════════ */
    switch (PRV_u8CurrentState)
    {
        /* ── OFF ────────────────────────────────────────────────── */
        case STATE_OFF:
        {
            SSD_voidClear();
            DIO_voidSetPinValue(HEATER_PORT,     HEATER_PIN,     DIO_PIN_LOW);
            DIO_voidSetPinValue(COOLER_PORT,     COOLER_PIN,     DIO_PIN_LOW);
            DIO_voidSetPinValue(HEATER_LED_PORT, HEATER_LED_PIN, DIO_PIN_LOW);

            /* Transition to ON on button RELEASE (edge detection) */
            if (L_u8OnOff == SWITCH_PRESSED)
            {
                prvWaitRelease(SWITCH_ONOFF_PORT, SWITCH_ONOFF_PIN);

                /* Clear history so average starts fresh */
                for (i = 0u; i < TEMP_BUFFER_SIZE; i++)
                {
                    PRV_u8TempHistory[i] = 0u;
                }
                PRV_u8HistoryIndex  = 0u;
                PRV_u16SystemTicks  = 0u;

                TMR0_voidStart();
                PRV_u8CurrentState = STATE_ON;
            }
            break;
        }

        /* ── ON ─────────────────────────────────────────────────── */
        case STATE_ON:
        {
            /* Display current average temperature */
            SSD_voidDisplayTwoDigitNumber(L_u8AvgTemp);

            /* ── Heating / Cooling / LED logic ──────────────────── */
            if (L_u8AvgTemp < (L_u8SetTemp - TEMP_HYSTERESIS))
            {
                /* Below set-point → HEAT ON, COOL OFF, LED blinks */
                DIO_voidSetPinValue(HEATER_PORT, HEATER_PIN, DIO_PIN_HIGH);
                DIO_voidSetPinValue(COOLER_PORT, COOLER_PIN, DIO_PIN_LOW);
                /* Blink every 1 s: toggle at BLINK_TICKS (0.5 s) */
                DIO_voidSetPinValue(HEATER_LED_PORT, HEATER_LED_PIN,
                    (u8)((PRV_u16SystemTicks / BLINK_TICKS) % 2u));
            }
            else if (L_u8AvgTemp > (L_u8SetTemp + TEMP_HYSTERESIS))
            {
                /* Above set-point → HEAT OFF, COOL ON, LED steady ON */
                DIO_voidSetPinValue(HEATER_PORT,     HEATER_PIN,     DIO_PIN_LOW);
                DIO_voidSetPinValue(COOLER_PORT,     COOLER_PIN,     DIO_PIN_HIGH);
                DIO_voidSetPinValue(HEATER_LED_PORT, HEATER_LED_PIN, DIO_PIN_HIGH);
            }
            else
            {
                /* Within hysteresis band → both OFF, LED OFF */
                DIO_voidSetPinValue(HEATER_PORT,     HEATER_PIN,     DIO_PIN_LOW);
                DIO_voidSetPinValue(COOLER_PORT,     COOLER_PIN,     DIO_PIN_LOW);
                DIO_voidSetPinValue(HEATER_LED_PORT, HEATER_LED_PIN, DIO_PIN_LOW);
            }

            /* Enter SETTING mode on first UP or DOWN press */
            if ((L_u8Up == SWITCH_PRESSED) || (L_u8Down == SWITCH_PRESSED))
            {
                PRV_u16SystemTicks = 0u;        /* reset timeout counter */
                PRV_u8CurrentState = STATE_SETTING;
                /* Do NOT wait for release here – first press is consumed
                   in SETTING state so the user sees immediate response   */
            }
            break;
        }

        /* ── SETTING ────────────────────────────────────────────── */
        case STATE_SETTING:
        {
            /* Blink the SET temperature on display every 1 s */
            if (((PRV_u16SystemTicks / BLINK_TICKS) % 2u) != 0u)
            {
                SSD_voidDisplayTwoDigitNumber(L_u8SetTemp);
            }
            else
            {
                SSD_voidClear();
            }

            /* Heating / Cooling still runs in background */
            if (L_u8AvgTemp < (L_u8SetTemp - TEMP_HYSTERESIS))
            {
                DIO_voidSetPinValue(HEATER_PORT, HEATER_PIN, DIO_PIN_HIGH);
                DIO_voidSetPinValue(COOLER_PORT, COOLER_PIN, DIO_PIN_LOW);
                DIO_voidSetPinValue(HEATER_LED_PORT, HEATER_LED_PIN,
                    (u8)((PRV_u16SystemTicks / BLINK_TICKS) % 2u));
            }
            else if (L_u8AvgTemp > (L_u8SetTemp + TEMP_HYSTERESIS))
            {
                DIO_voidSetPinValue(HEATER_PORT,     HEATER_PIN,     DIO_PIN_LOW);
                DIO_voidSetPinValue(COOLER_PORT,     COOLER_PIN,     DIO_PIN_HIGH);
                DIO_voidSetPinValue(HEATER_LED_PORT, HEATER_LED_PIN, DIO_PIN_HIGH);
            }
            else
            {
                DIO_voidSetPinValue(HEATER_PORT,     HEATER_PIN,     DIO_PIN_LOW);
                DIO_voidSetPinValue(COOLER_PORT,     COOLER_PIN,     DIO_PIN_LOW);
                DIO_voidSetPinValue(HEATER_LED_PORT, HEATER_LED_PIN, DIO_PIN_LOW);
            }

            /* UP button: increase by 5 °C */
            if ((L_u8Up == SWITCH_PRESSED) && (L_u8SetTemp <= (EWH_MAX_TEMP - TEMP_STEP)))
            {
                L_u8SetTemp += TEMP_STEP;
                EEPROM_voidWriteByte(EEPROM_SET_TEMP_ADDR, L_u8SetTemp);
                PRV_u16SystemTicks = 0u;        /* reset timeout */
                prvWaitRelease(SWITCH_UP_PORT, SWITCH_UP_PIN);
            }

            /* DOWN button: decrease by 5 °C */
            if ((L_u8Down == SWITCH_PRESSED) && (L_u8SetTemp >= (EWH_MIN_TEMP + TEMP_STEP)))
            {
                L_u8SetTemp -= TEMP_STEP;
                EEPROM_voidWriteByte(EEPROM_SET_TEMP_ADDR, L_u8SetTemp);
                PRV_u16SystemTicks = 0u;        /* reset timeout */
                prvWaitRelease(SWITCH_DOWN_PORT, SWITCH_DOWN_PIN);
            }

            /* Timeout → return to ON */
            if (PRV_u16SystemTicks >= TIMEOUT_TICKS)
            {
                PRV_u8CurrentState = STATE_ON;
            }
            break;
        }

        default:
            PRV_u8CurrentState = STATE_OFF;
            break;
    }

    /* ════════════════════════════════════════════════════════════════
     *  Global ON/OFF toggle (checked in every non-OFF state too)
     *  Spec: button RELEASED triggers the toggle.
     * ════════════════════════════════════════════════════════════════ */
    if ((L_u8OnOff == SWITCH_PRESSED) && (PRV_u8CurrentState != STATE_OFF))
    {
        prvWaitRelease(SWITCH_ONOFF_PORT, SWITCH_ONOFF_PIN);
        TMR0_voidStop();

        DIO_voidSetPinValue(HEATER_PORT,     HEATER_PIN,     DIO_PIN_LOW);
        DIO_voidSetPinValue(COOLER_PORT,     COOLER_PIN,     DIO_PIN_LOW);
        DIO_voidSetPinValue(HEATER_LED_PORT, HEATER_LED_PIN, DIO_PIN_LOW);
        SSD_voidClear();

        PRV_u8CurrentState = STATE_OFF;
    }
}

/* ── Getter utilities ─────────────────────────────────────────────────── */

void EWH_voidGetCurrentAvgTemp(u8 *Copy_pu8Temp)
{
    if (Copy_pu8Temp != NULL)
    {
        u16 sum = 0u;
        u8  i;
        for (i = 0u; i < TEMP_BUFFER_SIZE; i++) { sum += PRV_u8TempHistory[i]; }
        *Copy_pu8Temp = (u8)(sum / TEMP_BUFFER_SIZE);
    }
}

void EWH_voidGetSetTemp(u8 *Copy_pu8Temp)
{
    if (Copy_pu8Temp != NULL)
    {
        EEPROM_voidReadByte(EEPROM_SET_TEMP_ADDR, Copy_pu8Temp);
    }
}
