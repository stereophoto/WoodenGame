#include <Stepper.h>

// Define the number of steps per revolution for the stepper motor
const int stepsPerRevolution = 2048;

// Initialize the Stepper library with the motor interface type and pin 
connections
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

// Button pins
const int rotateButtonPin = 2;
const int resetButtonPin = 3;
int rotateButtonState = HIGH;
int lastRotateButtonState = HIGH;
int resetButtonState = HIGH;
int lastResetButtonState = HIGH;

// Angle increment
const int angleIncrement = 45;  // Adjust this value to change the angle 
increment

// Total angle
int totalAngle = 0;

void setup() {
  // Set the speed of the motor (in RPM)
  myStepper.setSpeed(60);  // Adjust this value to change the motor speed

  // Initialize the button pins
  pinMode(rotateButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
}

void loop() {
  // Read the state of the rotate button
  rotateButtonState = digitalRead(rotateButtonPin);

  // Check if the rotate button state has changed
  if (rotateButtonState != lastRotateButtonState) {
    // If the rotate button is pressed (LOW state)
    if (rotateButtonState == LOW) {
      // Rotate the motor by the specified angle increment
      myStepper.step(angleIncrement);
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
      // Rotate the motor in the reverse direction by the total angle
      myStepper.step(-totalAngle);
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
