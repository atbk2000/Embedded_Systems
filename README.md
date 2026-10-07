# Embedded Systems Projects

Projects for **STM32L432KBUx** (ARM Cortex-M4, Nucleo-32) and **TM4C1294** (ARM Cortex-M4F, Tiva C series).

---

## Acknowledgment

The **STM32** projects in this repository are based on the Udemy course **[Embedded Systems Bare-Metal Programming Ground Up™ (STM32)](https://www.udemy.com/)** by Israel Gbati. The course teaches register-level programming on an STM32F4 device, and I followed its project progression as the learning path for this repository.

> This project is an independent learning effort and is not affiliated with or endorsed by the course author or Udemy. All course content remains the property of its author. If you want to learn this material properly, I recommend taking the course.

The **TM4C1294** projects are independent work and are not derived from the course.

---

## Repository Structure

```
.
├── stm32l432/
│   ├── 1_.../
│   ├── 7_input_interrupt/
│   ├── 10_systick_interrupt/
│   └── ...
├── tm4c1294/
│   └── ...
└── README.md
```

Each project folder is self-contained and has `Src/`, `Inc/` and `Startup/` directories, plus the linker script.

---

## Getting Started

### STM32L432

**Requirements**

- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) (bundles `arm-none-eabi-gcc` and the debugger)
- NUCLEO-L432KC board and a micro USB cable

### TM4C1294

**Requirements**

- Toolchain, e.g. Code Composer Studio / Keil uVision / arm-none-eabi-gcc + OpenOCD
- Board and drivers, e.g. ICDI/Stellaris driver, and a micro USB cable

---

## References

- [STM32L432KB datasheet](https://www.st.com/en/microcontrollers-microprocessors/stm32l432kb.html)
- RM0394: STM32L41xxx/42xxx/43xxx/44xxx/45xxx/46xxx reference manual
- TM4C1294NCPDT datasheet and TivaWare documentation
- MPU-6000/MPU-6050 register map and product specification (InvenSense/TDK)

---
