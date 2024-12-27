#include <BleKeyboard.h>  // Include the BLE Keyboard library

// BLE Keyboard setup
BleKeyboard bleKeyboard("ESP32 Steering", "Eshal's Setup", 100);

// Pin Definitions for Buttons
#define ACCELERATOR_PIN 21  // Accelerator button pin (GPIO21)
#define BRAKE_PIN 22        // Brake button pin (GPIO22)

int potentiometerPin = 34;  // Connect potentiometer to GPIO34 (ADC1_CH6)

int minValue = 0;           // Minimum potentiometer value
int maxValue = 4095;        // Maximum potentiometer value
int neutralValue = 2048;    // Neutral position (centered)

bool isAcceleratorPressed = false;  // Button press state for accelerator
bool isBrakePressed = false;        // Button press state for brake

unsigned long lastDebounceTime = 0;  // Last time the button state was updated
unsigned long debounceDelay = 50;    // Debounce delay (50 ms)

void setup() {
  Serial.begin(115200);  // Start Serial Monitor

  // Set up the potentiometer and button pins as input with internal pull-up resistors
  pinMode(potentiometerPin, INPUT);
  pinMode(ACCELERATOR_PIN, INPUT_PULLUP);  // Pull-up resistor for accelerator button
  pinMode(BRAKE_PIN, INPUT_PULLUP);        // Pull-up resistor for brake button

  // Initialize the BLE Keyboard
  Serial.println("Starting BLE Keyboard...");
  bleKeyboard.begin();
}

void loop() {
  if (bleKeyboard.isConnected()) {  // Check if BLE keyboard is connected

    // Read the current state of the potentiometer for steering
    int potValue = analogRead(potentiometerPin);
    Serial.print("Potentiometer Value: ");
    Serial.println(potValue);

    // Handle Steering Left and Right (based on potentiometer position)
    if (potValue < (neutralValue - 100)) {
      // Steering Right (for potentiometer reading lower than neutral value)
      int intensity = map(potValue, minValue, neutralValue - 100, 10, 100); // Map to intensity
      Serial.print("Turning Right with Intensity: ");
      Serial.println(intensity);
      bleKeyboard.press(KEY_RIGHT_ARROW);  // Simulate pressing right arrow (steering right)
      delay(intensity);
      bleKeyboard.releaseAll();
    } else if (potValue > (neutralValue + 100)) {
      // Steering Left (for potentiometer reading higher than neutral value)
      int intensity = map(potValue, neutralValue + 100, maxValue, 10, 100); // Map to intensity
      Serial.print("Turning Left with Intensity: ");
      Serial.println(intensity);
      bleKeyboard.press(KEY_LEFT_ARROW);  // Simulate pressing left arrow (steering left)
      delay(intensity);
      bleKeyboard.releaseAll();
    } else {
      // Neutral Position (when potentiometer is around the center)
      Serial.println("Neutral Position");
      bleKeyboard.releaseAll();
    }

    // Read the current state of the accelerator and brake buttons (LOW means pressed)
    bool currentAcceleratorState = digitalRead(ACCELERATOR_PIN) == LOW;
    bool currentBrakeState = digitalRead(BRAKE_PIN) == LOW;

    // Check if enough time has passed to debounce the accelerator button
    if ((millis() - lastDebounceTime) > debounceDelay) {
      // Debounce logic for accelerator button press/release
      if (currentAcceleratorState && !isAcceleratorPressed) {
        Serial.println("Accelerator Pressed");
        bleKeyboard.press(KEY_UP_ARROW);  // Send "Up Arrow" key press
        isAcceleratorPressed = true;
      } else if (!currentAcceleratorState && isAcceleratorPressed) {
        Serial.println("Accelerator Released");
        bleKeyboard.release(KEY_UP_ARROW);  // Release "Up Arrow" key
        isAcceleratorPressed = false;
      }

      // Debounce logic for brake button press/release
      if (currentBrakeState && !isBrakePressed) {
        Serial.println("Brake Pressed");
        bleKeyboard.press(KEY_DOWN_ARROW);  // Send "Down Arrow" key press
        isBrakePressed = true;
      } else if (!currentBrakeState && isBrakePressed) {
        Serial.println("Brake Released");
        bleKeyboard.release(KEY_DOWN_ARROW);  // Release "Down Arrow" key
        isBrakePressed = false;
      }

      // Update the debounce time
      lastDebounceTime = millis();
    }

    // If the accelerator button is pressed, keep sending the "UP arrow" key
    if (isAcceleratorPressed) {
      Serial.println("Accelerating...");
      bleKeyboard.press(KEY_UP_ARROW);  // Continue pressing the "Up Arrow" key
    } else {
      bleKeyboard.release(KEY_UP_ARROW);  // Release the "Up Arrow" key if button is not pressed
    }

    delay(10);  // Small delay to avoid flooding the serial monitor
  }
}
