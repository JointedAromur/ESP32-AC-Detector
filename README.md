# ESP32 Non-Contact AC Detector
A DIY electromagnetic field (EMF) sensor built with an ESP32 that detects 50/60Hz AC voltage through walls without physical contact.

## Features
- **Real-time Signal Analysis**: Calculates RMS values to determine field strength.
- **Visual Feedback**: Built-in LED triggers when near a live AC source.
- **Serial Plotter Support**: View the literal 60Hz sine wave via the Arduino Serial Plotter.

## Hardware Required
- ESP32 Development Board
- Jumper wires (Antenna)

## How to Use
1. Flash the code using PlatformIO.
2. Open the Serial Plotter at 115200 baud.
3. Bring the antenna tip near an outlet or power cable.


## 🛠 How it Works

The project operates at the intersection of **Electromagnetic Induction** and **Statistical Signal Processing**.

### 1. Physical Principle: The Floating Antenna
AC power lines in walls carry a current that oscillates at **50Hz/60Hz**. This creates a fluctuating electromagnetic field. By connecting a "floating" jumper wire to a high-impedance ADC (Analog-to-Digital Converter) pin on the ESP32, the wire acts as a capacitive probe. It picks up the ambient field via induction, which manifests as a tiny, oscillating voltage on the pin.

### 2. The Shielding Effect
To ensure the detector is directional, a **grounded shield** is used. By wrapping a wire connected to `GND` around the base of the antenna, we create a partial Faraday cage. This drains background EMI from your hand or nearby devices to the ground, leaving only the exposed tip sensitive to the target field.

### 3. Computation: RMS Signal Processing
Raw ADC values are noisy and include a DC offset. To turn this into a stable "strength" value, the firmware performs the following:

* **High-Speed Sampling:** The ADC is sampled at ~2kHz, satisfying the Nyquist theorem for a 60Hz wave.
* **DC Offset Removal:** We calculate the average of a sample batch and subtract it from each reading to center the wave at zero.
* **RMS Calculation:** We use the **Root Mean Square** formula to calculate effective magnitude:
  
  $$x_{rms} = \sqrt{\frac{1}{n} \sum_{i=1}^{n} x_i^2}$$

### 4. Logic & Feedback
The calculated RMS value is compared against a defined `threshold`. If the field strength exceeds this limit, the ESP32 triggers the onboard LED (GPIO 2), providing real-time visual feedback of hidden live wires.


## 💻 Tech Stack

- **Language:** C++
- **Framework:** Arduino Framework (ESP32 Core)
- **Environment:** PlatformIO / VS Code
- **Hardware:** ESP32 (D0WD-V3)
- **Tools:** Arduino Serial Plotter (for signal visualization)