# IR Receiver Project

This project implements an IR receiver using an STM32F103C8T6 (Blue Pill) microcontroller.

The IR receiver module captures signals from a standard TV remote. External interrupts detect signal edges, while TIM2 measures the time between them. The measured timings are stored and decoded according to the NEC protocol. Depending on the received command, the microcontroller controls an LED and changes its operating mode.

## What I Learned

- GPIO configuration
- External interrupts (EXTI)
- Hardware timers
- Measuring pulse widths
- NEC protocol decoding
- Interrupt-driven programming
- Bare-metal STM32 development
- Debugging with a logic analyzer

## Hardware

- STM32F103C8T6 (Blue Pill)
- IR Receiver Module
- LED
- TV Remote Control
- ST-Link Programmer
