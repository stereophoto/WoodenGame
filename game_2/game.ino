#include <CheapStepper.h>

// Define the number of steps per revolution for the stepper motor
const int stepsPerRevolution = 2048;

// Initialize the CheapStepper library with the motor interface type and pin connections
CheapStepper myStepper(22, 24, 26, 28); // Modify the pin connections 
according to your setup

// Button pins
const int rotateButtonPin = A1;
const int resetButtonPin = A2;
int rotateButtonState = HIGH;
int lastRotateButtonState = HIGH;
int resetButtonState = HIGH;
int lastResetButtonState = HIGH;

// Angle increment
const int angleIncrement = 720;  // Adjust this value to change the angle increment

// Total angle
int totalAngle = 0;

void setup() {
  // Set the speed of the motor (in RPM)
  myStepper.setRpm(20);  // Adjust this value to change the motor speed

  // Initialize the button pins
  pinMode(rotateButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the state of the rotate button
  rotateButtonState = digitalRead(rotateButtonPin);

  // Check if the rotate button state has changed
  if (rotateButtonState != lastRotateButtonState) {
    // If the rotate button is pressed (LOW state)
    if (rotateButtonState == LOW) {
      Serial.println("Rotate button pressed");

      // Rotate the motor by the specified angle increment
      myStepper.moveDegrees(true, angleIncrement); // Rotate clockwise
      // Add the angle increment to the total angle
      totalAngle += angleIncrement;
    }

    // Delay to avoid multiple rapid button presses
    delay(50);
  }

  // Read the state of the reset button
  resetButtonState = digitalRead(resetButtonPin);

  // Check if the reset button state has changed
  if (resetButtonState != lastResetButtonState) {
    // If the reset button is pressed (LOW state)
    if (resetButtonState == LOW) {
      Serial.println("Reset button pressed");

      // Rotate the motor in the reverse direction by the total angle
      myStepper.moveDegrees(false, totalAngle); // Rotate counter-clockwise
      // Reset the total angle to 0
      totalAngle = 0;
    }

    // Delay to avoid multiple rapid button presses
    delay(50);
  }

  // Update the last button states
  lastRotateButtonState = rotateButtonState;
  lastResetButtonState = resetButtonState;
}

