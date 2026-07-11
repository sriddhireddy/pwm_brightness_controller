# STM32 PWM LED Brightness Controller (Register-Level Programming)

A register-level embedded systems project built on the **STM32 Nucleo-F446RE** development board. This project demonstrates how to generate **hardware PWM (Pulse Width Modulation)** using **TIM2 Channel 1** to control the brightness of the onboard **LD2 LED (PA5)**. The brightness is adjusted using the onboard **User Button (PC13)**, while the selected duty cycle is displayed over UART.

---

## Features

- Register-level programming (No HAL / CubeMX generated code)
- Modular GPIO, UART, and Timer drivers
- Hardware PWM generation using TIM2 Channel 1
- Button-controlled LED brightness
- UART feedback displaying current duty cycle
- Clean driver-based architecture
- 1 kHz PWM signal generation
- Adjustable duty cycle (0%, 25%, 50%, 75%, 100%)

---

## Hardware Used

- STM32 Nucleo-F446RE
- STM32CubeIDE
- Onboard LD2 LED (PA5)
- Onboard User Button (PC13)
- USB UART (Virtual COM Port)

---

## Project Structure

```
STM32_PWM_Controller/
│
├── Core/
│   ├── Src/
│   │   ├── main.c
│   │   ├── gpio_driver.c
│   │   ├── uart_driver.c
│   │   └── timer_driver.c
│   │
│   └── Inc/
│       ├── gpio_driver.h
│       ├── uart_driver.h
│       └── timer_driver.h
│
├── Images/
│
└── README.md
```

---

# Project Architecture

```
                    User Button (PC13)
                           │
                           ▼
                  GPIO Button Driver
                           │
                           ▼
                      Application
                           │
                           ▼
              Timer_SetDutyCycle()
                           │
                           ▼
                   Timer Driver (TIM2)
                           │
                           ▼
               PWM Output (TIM2_CH1)
                           │
                           ▼
                    GPIO Alternate Function
                           │
                           ▼
                     PA5 (LD2 LED)

UART Driver
     │
     ▼
Displays Current Duty Cycle
```

---

# PWM Configuration

## Timer Configuration

| Parameter | Value |
|-----------|------:|
| Timer | TIM2 |
| Channel | Channel 1 |
| GPIO Pin | PA5 |
| Alternate Function | AF1 |
| Timer Clock | 16 MHz |
| Prescaler | 15 |
| ARR | 999 |
| PWM Frequency | 1 kHz |

---

## Duty Cycle Levels

| Duty Cycle | CCR1 Value |
|-----------:|-----------:|
| 0% | 0 |
| 25% | 249 |
| 50% | 499 |
| 75% | 749 |
| 100% | 999 |

---

# Driver Architecture

## GPIO Driver

Responsibilities:

- GPIO initialization
- Configure PA5 as Alternate Function
- Configure PC13 as Input
- Read button state
- Edge detection for button press

Functions:

```c
GPIO_Init();
GPIO_ReadButton();
GPIO_ButtonPressed();
```

---

## UART Driver

Responsibilities:

- UART initialization
- Character transmission
- String transmission
- Integer transmission

Functions:

```c
UART_Init();
UART_WriteChar();
UART_WriteString();
UART_WriteInt();
```

---

## Timer Driver

Responsibilities:

- Timer initialization
- PWM configuration
- Start/Stop timer
- Change duty cycle

Functions:

```c
Timer_Init();
Timer_PWM_Init();
Timer_Start();
Timer_Stop();
Timer_SetDutyCycle();
```

---

# Register Configuration

## GPIO

```
RCC->AHB1ENR
        │
        ▼
Enable GPIOA Clock

GPIOA->MODER
        │
        ▼
Alternate Function Mode

GPIOA->AFR[0]
        │
        ▼
AF1 (TIM2_CH1)
```

---

## Timer

```
RCC->APB1ENR
        │
        ▼
Enable TIM2 Clock

TIM2->PSC
        │
        ▼
15

TIM2->ARR
        │
        ▼
999

TIM2->CNT
        │
        ▼
0
```

---

## PWM

```
TIM2->CCMR1
        │
        ▼
PWM Mode 1

TIM2->CCR1
        │
        ▼
Duty Cycle

TIM2->CCER
        │
        ▼
Enable Channel 1

TIM2->CR1
        │
        ▼
Start Timer
```

---

# How PWM Works

The timer continuously counts from **0** to **999**.

```
CNT

0
1
2
3
...
999
0
```

The compare register (`CCR1`) determines how long the output remains HIGH.

Example:

```
ARR = 999
CCR1 = 250

HIGH ───────────────┐
                    │
LOW                 └────────────────────

0                 250                 999
```

Changing only the `CCR1` register changes the duty cycle while maintaining a constant PWM frequency.

---

# Program Flow

```
System Reset
      │
      ▼
GPIO_Init()
      │
      ▼
UART_Init()
      │
      ▼
Timer_Init()
      │
      ▼
Timer_PWM_Init()
      │
      ▼
Timer_SetDutyCycle(0)
      │
      ▼
Timer_Start()
      │
      ▼
while(1)
      │
      ▼
Button Pressed?
      │
      ├── No
      │      │
      │      ▼
      │   Continue
      │
      └── Yes
             │
             ▼
      Increase Duty Cycle
             │
             ▼
     Wrap after 100%
             │
             ▼
    Timer_SetDutyCycle()
             │
             ▼
UART Prints Current Duty Cycle
```

---

# UART Output

```
Duty Cycle: 25%

Duty Cycle: 50%

Duty Cycle: 75%

Duty Cycle: 100%

Duty Cycle: 0%
```

---

# Results

- Successfully generated a **1 kHz PWM signal** using **TIM2 Channel 1**.
- Controlled the onboard **LD2 LED brightness** using hardware PWM.
- Implemented modular GPIO, UART, and Timer drivers.
- Demonstrated register-level peripheral programming without using HAL libraries.
- Displayed the current duty cycle over UART after every button press.

---

# Future Improvements

- Software debounce using SysTick timestamps
- UART-based brightness control
- Adjustable PWM frequency
- RGB LED control
- Multi-channel PWM support
- Fade-in / Fade-out effects
- Interrupt-based button handling
- Generic timer driver supporting multiple timers

---

# Images

## Hardware Setup

<p align="center">
  <img src="Images/hardware_setup.jpg" alt="Hardware Setup" width="700">
</p>

## UART Output

<p align="center">
  <img src="Images/uart_output.png" alt="UART Output" width="700">
</p>

---

# Learning Outcomes

This project demonstrates practical understanding of:

- STM32 register-level programming
- GPIO Alternate Function configuration
- Timer peripheral configuration
- PWM generation
- Hardware compare mechanism
- Driver-based firmware architecture
- Modular embedded software design
- UART communication
- Button edge detection

---

## Author

**Riddhi Sridhar**

Electronics and Communication Engineering  
RV College of Engineering

---