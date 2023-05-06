#include <Wire.h>
#include <TM1637Display.h>

// Pin definitions for TM1637 display
#define CLK_PIN 22
#define DIO_PIN 24

// Define TM1637 display
TM1637Display display(CLK_PIN, DIO_PIN);

// Define common buttons count and properties
const int buttonCount = 3;
int buttonPins[buttonCount] = {2, 3, 4};
int buttonPoints[buttonCount] = {-5, 10, 15};

// Define reset button
int resetPin = 5;

// Define default player's score
int score = 0;

// Define default delay in millis
int delayDefault = 10;

// Array to store previous button states
int previousButtonStates[buttonCount] = {HIGH, HIGH, HIGH};

void setup() {
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(resetPin, INPUT_PULLUP);

  display.setBrightness(2);
  display.showNumberDec(score);
}

void loop() {
  handleButtons();
}

// Handle buttons state
void handleButtons() {
  // Add points to the current user's score by pressing the "point" 
  // buttons
  for (int i = 0; i < buttonCount; i++) {
    int currentButtonState = digitalRead(buttonPins[i]);
    if (currentButtonState == LOW && previousButtonStates[i] == HIGH) {
      score = changeDisplayNumberWithDelay(score, buttonPoints[i], delayDefault);
    }
    previousButtonStates[i] = currentButtonState;
  }

  // Reset current user score by using "reset" button
  if (digitalRead(resetPin) == LOW) {
    score = changeDisplayNumber(0);
  }
}

int changeDisplayNumberWithDelay(int currentNumber, int numberToChange, int changingDelay) {
  int step = (numberToChange > 0) ? 1 : -1;

  int currentScore = currentNumber;
  int targetScore = currentScore + numberToChange;

  if (targetScore < 0) {
    targetScore = 0;
  }

  while (currentScore != targetScore) {
    currentScore += step;
    display.showNumberDec(currentScore);
    delay(changingDelay);
  }

  return targetScore;
}

int changeDisplayNumber(int numberToChange) {
  display.showNumberDec(numberToChange);
  return numberToChange;
}
