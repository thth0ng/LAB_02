# HCMUT - Microprocessors & Microcontrollers (CO3009)
## LAB 02: Timer Interrupt & LED Scanning (7-Segment & LED Matrix)

* **University:** Ho Chi Minh City University of Technology (HCMUT - ĐHQG-HCM)
* **Target Microcontroller:** STM32F103C6 (ARM Cortex-M3)
* **Toolchain:** STM32CubeIDE 1.8.0+, Proteus Design Suite 8.10+

---

## 📋 Project & Exercise Structure

The lab exercises are organized into 3 projects corresponding to the implementation stages:

| Project | Exercises Included | Key Topics / Descriptions | Source Code | Proteus Simulation |
| :--- | :--- | :--- | :--- | :--- |
| **EX_14** | **Ex 1 – Ex 4** | • Hardware Timer Interrupt (`TIM2` period 10ms)<br>• 7-Segment Display Scanning (`display7SEG()`)<br>• 4-Digit Display Multiplexing (`update7SEG()`)<br>• Blinking DOT / Colon LEDs | [EX_14/Core/Src/main.c](EX_14/Core/Src/main.c) | [EX_14/ex14.pdsprj](EX_14/ex14.pdsprj) |
| **EX_58** | **Ex 5 – Ex 8** | • Digital Clock System (HH:MM)<br>• `updateClockBuffer()` buffer synchronization<br>• Software Timer Architecture (`setTimer()`, `timer_run()`)<br>• Multi-Timer Management (Clock, Blink DOT, LED Scan) | [EX_58/Core/Src/main.c](EX_58/Core/Src/main.c) | [EX_58/EX58.pdsprj](EX_58/EX58.pdsprj) |
| **EX_910** | **Ex 9 – Ex 10** | • 8x8 LED Matrix Display (`updateLEDMatrix()`)<br>• Character "A" Matrix Bitmap Rendering<br>• Column Multiplexing via ULN2803 (`ENM0`–`ENM7`)<br>• Horizontal Matrix Scrolling Animation (`shift_left()`) | [EX_910/Core/Src/main.c](EX_910/Core/Src/main.c) | [EX_910/EX910.pdsprj](EX_910/EX910.pdsprj) |

---

## 🛠️ Hardware & Pin Configuration Summary

### 1. 7-Segment LED Displays (Common Anode)
* **Segment Control (Port B - Active LOW):**
  * `PB0`: Segment A
  * `PB1`: Segment B
  * `PB2`: Segment C
  * `PB3`: Segment D
  * `PB4`: Segment E
  * `PB5`: Segment F
  * `PB6`: Segment G
* **Digit Enable Transistors (Port A - Active LOW via PNP Transistors):**
  * `PA6`: EN0 (Digit 1 - Hour tens)
  * `PA7`: EN1 (Digit 2 - Hour units)
  * `PA8`: EN2 (Digit 3 - Minute tens)
  * `PA9`: EN3 (Digit 4 - Minute units)
* **Time Separator Colon / DOT LED:**
  * `PA4`: DOT LED (Blinks at 1 Hz)

### 2. 8x8 LED Matrix (Exercises 9 & 10)
* **Column Enable (Port A - Active HIGH via ULN2803 driver):**
  * `PA2`: ENM0 (Column 0)
  * `PA3`: ENM1 (Column 1)
  * `PA10`: ENM2 (Column 2)
  * `PA11`: ENM3 (Column 3)
  * `PA12`: ENM4 (Column 4)
  * `PA13`: ENM5 (Column 5)
  * `PA14`: ENM6 (Column 6)
  * `PA15`: ENM7 (Column 7)
* **Row Data (Port B - Active HIGH):**
  * `PB8`: ROW0
  * `PB9`: ROW1
  * `PB10`: ROW2
  * `PB11`: ROW3
  * `PB12`: ROW4
  * `PB13`: ROW5
  * `PB14`: ROW6
  * `PB15`: ROW7

---

## ⏱️ Timer Architecture & Software Timers

### Hardware Timer (TIM2)
* **Clock Source:** Internal HSI (8 MHz)
* **Prescaler:** `7999` $\rightarrow$ Timer Clock = $8\text{ MHz} / (7999 + 1) = 1\text{ kHz}$ (1 ms tick)
* **Period (ARR):** `9` $\rightarrow$ Interrupt Period = $(9 + 1) \times 1\text{ ms} = 10\text{ ms}$
* **Interrupt Callback:** `HAL_TIM_PeriodElapsedCallback()` invokes software timer ticks `timer_run()` every 10 ms.

### Software Timers
* **Timer 0 (Clock Update):** Period 1000 ms – increments second, minute, and hour.
* **Timer 1 (DOT Blink):** Period 1000 ms – toggles `DOT_Pin` (PA4).
* **Timer 2 (7-Segment Scanning):** Period 250 ms – scans next 7-segment digit (4 digits $\times$ 250 ms = 1000 ms full frame cycle).
* **Timer 3 (LED Matrix Scanning):** Period 10 ms – scans next column of 8x8 matrix (8 columns $\times$ 10 ms = 80 ms refresh rate ~ 12.5 Hz).
* **Timer 4 (Matrix Animation Shift):** Period 200 ms – shifts character bitmap left by 1 column.

---

## 🚀 How to Run & Simulate

### 1. Build in STM32CubeIDE
1. Open **STM32CubeIDE** (Workspace: `LAB_02`).
2. Go to **File** $\rightarrow$ **Import...** $\rightarrow$ **Existing Projects into Workspace**.
3. Select the desired project folder (`EX_14`, `EX_58`, or `EX_910`).
4. Click **Build Project** (Hammer icon). The output `.hex` and `.elf` binaries will be generated inside `Debug/`.

### 2. Simulate in Proteus
1. Open **Proteus Design Suite 8.10+**.
2. Open the corresponding schematic:
   - `EX_14/ex14.pdsprj` for Ex 1 – 4
   - `EX_58/EX58.pdsprj` for Ex 5 – 8
   - `EX_910/EX910.pdsprj` for Ex 9 – 10
3. Double-click the **STM32F103C6** component and verify that the **Program File** is linked to the compiled `.hex` file in the project's `Debug/` folder.
4. Click **Run the simulation** (Play button) to view the operation.
