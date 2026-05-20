# 🌡️ Electric Water Heater Controller

An intelligent embedded water heater controller built on AVR (ATmega32) featuring automatic temperature regulation, persistent settings via external EEPROM, a 7-segment display interface, and dual heating/cooling element control.

---

## 📌 Project Overview

This system simulates a smart electric water heater that maintains water temperature within a configurable range. It reads temperature every 100ms, averages the last 10 readings for stable control decisions, and drives both a heating element (Peltier heater) and a cooling element (Peltier cooler) accordingly.

---

## ✨ Features

- 🌡️ **Real-time temperature sensing** — reads every 100ms, averaged over 10 samples
- 🎯 **Adjustable set temperature** — 35°C to 75°C in 5°C steps
- 💾 **EEPROM persistence** — set temperature survives power cycles
- 📟 **7-segment display** — shows current or set temperature with blink mode
- 🔥 **Dual-element control** — separate heating and cooling elements
- 💡 **Heating Element LED indicator** — blinks when heating, solid when cooling
- 🔘 **3-button interface** — UP, DOWN, ON/OFF

---

## 🗂️ System Architecture

```
  [UP Button] ──┐
  [DOWN Button]─┤──► ATmega32 MCU ──► Heating Element (Ceramic)
  [ON/OFF Btn]──┘         │
                           ├──► Cooling Element (Peltier)
  LM35 Sensor ──ADC──────► │
                           ├──► 7-Segment Display (x2)
  External EEPROM ◄─I2C──► │
                           └──► Heating Element LED
```

---

## ⚙️ Specifications

### 🌡️ Temperature Setting
| Parameter | Value |
|---|---|
| Minimum set temperature | 35°C |
| Maximum set temperature | 75°C |
| Step size | 5°C |
| Default set temperature | 60°C |
| Setting mode timeout | 5 seconds of no button press |

### 🔥 Heating / Cooling Logic
| Condition | Heating Element | Cooling Element |
|---|---|---|
| Current temp < Set temp − 5°C | **ON** | OFF |
| Current temp > Set temp + 5°C | OFF | **ON** |

### 📟 7-Segment Display Behavior
| State | Display |
|---|---|
| Default (ON state) | Current water temperature |
| Temperature setting mode | Set temperature — blinks every 1 second |
| OFF state | All segments OFF |

### 💡 Heating LED Behavior
| State | LED |
|---|---|
| Heating element ON | Blinks every 1 second |
| Cooling element ON | Solid ON |

### 🔘 ON/OFF Behavior
- On power connection → system starts in **OFF** state
- Pressing ON/OFF toggles between ON and OFF
- In OFF state → all display segments turn off

---

## 🧰 Components

| Component | Model | Purpose |
|---|---|---|
| Microcontroller | ATmega32 | Main controller |
| Temperature Sensor | LM35 / DS18B20 | Water temperature reading |
| External EEPROM | 24C08 | Persistent temperature storage |
| Heating Element | 3D Ceramic Heater | Raises water temperature |
| Cooling Element | Peltier Module | Lowers water temperature |
| Display | 2× 7-Segment | Temperature display |
| Solid State Relay | SSR | Element switching |
| Push Buttons | x3 | UP / DOWN / ON/OFF |
| LED | — | Heating status indicator |
| Cooling Fins & Fan | — | Thermal management |

---

## 🔌 Interfaces Used

- **ADC** — LM35 temperature sensor
- **I2C** — External EEPROM (24C08)
- **GPIO** — Buttons, LED, SSR control, 7-segment
- **Timer** — 100ms sampling, 1-second blink, 5-second timeout

---

## 🛠️ Tools & Environment

- **Language:** Embedded C
- **MCU:** ATmega32 (AVR)
- **Simulation:** Proteus
- **Programmer:** AVRDUDE / USBasp

---

## 👥 Team

Project built as part of the **Embedded Systems Diploma** at AMIT Learning.

---

## 📄 License

This project is for educational purposes.
