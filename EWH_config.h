/*
 * EWH_config.h
 *
 * Created: 2/27/2026
 *  Author: hamza
 *  Fixed : duplicate macros removed, unified naming
 */

#ifndef EWH_CONFIG_H_
#define EWH_CONFIG_H_

/* ── Temperature Constants ─────────────────────────────────────────────── */
#define EWH_INIT_TEMP         60u   /* Default set-temperature on first boot */
#define EWH_MIN_TEMP          35u   /* Minimum allowable set temperature      */
#define EWH_MAX_TEMP          75u   /* Maximum allowable set temperature      */
#define TEMP_BUFFER_SIZE      10u   /* Number of samples for rolling average  */
#define TEMP_HYSTERESIS        5u   /* Hysteresis band (±5 °C)               */
#define TEMP_STEP              5u   /* Step size per UP / DOWN press          */

/* ── Timing (multiples of 100 ms timer tick) ───────────────────────────── */
#define TICK_TIME_MS         100u   /* Timer callback period in ms            */
#define TIMEOUT_TICKS         50u   /* 5 s  → exit setting mode              */
#define BLINK_TICKS            5u   /* Toggle every 0.5 s → 1 s period       */

/* ── System States ─────────────────────────────────────────────────────── */
#define STATE_OFF              0u
#define STATE_ON               1u
#define STATE_SETTING          2u

/* ── EEPROM ────────────────────────────────────────────────────────────── */
#define EEPROM_SET_TEMP_ADDR  0x0000u

/* ── Hardware Pin Map ──────────────────────────────────────────────────── */
/* Heater element (SSR / ceramic heater)  */
#define HEATER_PORT           DIO_PORTB
#define HEATER_PIN            DIO_PIN4

/* Cooler element (Peltier / SSR)         */
#define COOLER_PORT           DIO_PORTB
#define COOLER_PIN            DIO_PIN5

/* Heating-element status LED             */
#define HEATER_LED_PORT       DIO_PORTB
#define HEATER_LED_PIN        DIO_PIN3

/* Push-buttons (active-HIGH / forward connection) */
#define SWITCH_UP_PORT        DIO_PORTD
#define SWITCH_UP_PIN         DIO_PIN2
#define SWITCH_DOWN_PORT      DIO_PORTD
#define SWITCH_DOWN_PIN       DIO_PIN3
#define SWITCH_ONOFF_PORT     DIO_PORTD
#define SWITCH_ONOFF_PIN      DIO_PIN7

#endif /* EWH_CONFIG_H_ */
