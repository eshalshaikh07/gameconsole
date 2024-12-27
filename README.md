# ESP32 BLE Steering and Control System

## Objective
This project uses an **ESP32** to simulate a BLE keyboard to control a system (like a game or a simulator) with an accelerator, brake, and steering functionality. The setup uses:
- **Accelerator Button**: Sends an "Up Arrow" key press to simulate acceleration.
- **Brake Button**: Sends a "Down Arrow" key press to simulate braking.
- **Potentiometer**: Controls steering by simulating left and right arrow key presses based on the potentiometer value.

This system provides continuous control for both acceleration and braking while allowing for dynamic steering with the potentiometer.

## Components
- **ESP32 Development Board**
- **2 Push Buttons** (for accelerator and brake)
- **1 Potentiometer** (for steering control)
- **BLE Keyboard Library** (to send keyboard inputs over Bluetooth)

## Pin Configuration
- **Accelerator Pin**: GPIO21
- **Brake Pin**: GPIO22
- **Potentiometer Pin**: GPIO34

## Libraries Required
- [BleKeyboard Library](https://github.com/T-vK/ESP32-BLE-Keyboard): BLE keyboard functionality for the ESP32.

To install the **BleKeyboard** library, go to Arduino IDE, click **Sketch** > **Include Library** > **Manage Libraries**, search for **BleKeyboard**, and install it.

## Setup
1. **Connect Buttons:**
   - **Accelerator Button**: Connect one side to **GPIO21** and the other to **GND**.
   - **Brake Button**: Connect one side to **GPIO22** and the other to **GND**.

2. **Connect Potentiometer:**
   - **Wiper (middle pin)**: Connect to **GPIO34** (ADC1_CH6).
   - **VCC (one outer pin)**: Connect to **3V**.
   - **GND (the other outer pin)**: Connect to **GND**.

3. **Install the necessary libraries** in Arduino IDE:
   - **BleKeyboard** library.
   - **ESP32 board** support in Arduino IDE.

4. **Upload the Code**:
   - Open the Arduino IDE and upload the code to your ESP32 board.

## Code Explanation

### Setup
- **BLE Keyboard** is initialized with the name "ESP32 Steering" and a specific setup (`Eshal's Setup`).
- **Pin Setup**: The potentiometer is connected to GPIO34, and the accelerator and brake buttons are connected to GPIO21 and GPIO22, respectively.
- **Debouncing** is implemented for the accelerator and brake buttons to ensure smooth and reliable button presses.

### Steering Control (Potentiometer)
- The potentiometer controls steering based on its position:
  - **Left**: When the potentiometer value is less than the neutral value.
  - **Right**: When the potentiometer value is greater than the neutral value.
  - **Neutral**: When the potentiometer value is within a certain threshold of the neutral value.

### Accelerator and Brake Button Control
- When the accelerator button is pressed, the **UP arrow** key is continuously pressed as long as the button is held.
- When the brake button is pressed, the **DOWN arrow** key is continuously pressed as long as the button is held.
- The buttons are debounced to avoid multiple presses being detected in a short time.

## How to Use
1. **Start the BLE Keyboard**:
   - Power on the ESP32 and ensure that the BLE device is paired with your computer or device.

2. **Control Steering**:
   - Rotate the potentiometer to steer:
     - **Left**: Potentiometer value lower than the neutral value.
     - **Right**: Potentiometer value higher than the neutral value.
     - **Neutral**: Potentiometer centered.

3. **Control Acceleration**:
   - Press and hold the **accelerator button** to simulate continuous acceleration (holding the button sends repeated "UP arrow" presses).
   - Release the button to stop the acceleration.

4. **Control Braking**:
   - Press and hold the **brake button** to simulate continuous braking (holding the button sends repeated "DOWN arrow" presses).
   - Release the button to stop the braking.

## Example Use Case
This setup can be used in a racing game or simulator where the ESP32 acts as a wireless controller:
- **Steering**: Controlled by the potentiometer (turning left or right).
- **Acceleration**: Controlled by the accelerator button (press and hold for continuous speed).
- **Braking**: Controlled by the brake button (press and hold for continuous braking).

## Troubleshooting
- If the BLE keyboard is not working, make sure your ESP32 is correctly paired with your device and that it's within range.
- Ensure that the **Accelerator** and **Brake** buttons are connected properly, and the pins are correctly defined in the code.

## Conclusion
This project provides a simple yet functional BLE-based steering and control system using an ESP32, suitable for gaming, simulation, or any other use that requires wireless input control.

## License
This project is licensed under the MIT License.
