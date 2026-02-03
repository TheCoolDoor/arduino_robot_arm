#include <Servo.h>
#include <Stepper.h>

// --- Stepper setup ---
const int stepsPerRevolution = 2038;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

// --- Servos ---
Servo servoSG90;
Servo servoMG995;

// --- SG90 control vars ---
int posSG90 = 0;
int dirSG90 = 1;
unsigned long lastSG90 = 0;
const unsigned long intervalSG90 = 15; // ms between steps

// --- MG995 control vars ---
int posMG995 = 0;
int dirMG995 = 1;
unsigned long lastMG995 = 0;
const unsigned long intervalMG995 = 20; // slightly slower typical

// --- Stepper control vars ---
long stepperCount = 0;
int stepperDir = 1;
unsigned long lastStepper = 0;
const unsigned long intervalStepper = 3; // ms per step

void setup() {
  // Attach servos
  servoSG90.attach(6);
  servoMG995.attach(5);

  // Stepper speed setting (RPM)
  myStepper.setSpeed(10);
}

void loop() {
  unsigned long now = millis();

  // ==== SG90 Linear Sweep ====
  if (now - lastSG90 >= intervalSG90) {
    lastSG90 = now;
    posSG90 += dirSG90;
    servoSG90.write(posSG90);
    if (posSG90 >= 180 || posSG90 <= 0) {
      dirSG90 = -dirSG90;
    }
  }

  // ==== MG995 Linear Sweep ====
  if (now - lastMG995 >= intervalMG995) {
    lastMG995 = now;
    posMG995 += dirMG995;
    servoMG995.write(posMG995);
    if (posMG995 >= 180 || posMG995 <= 0) {
      dirMG995 = -dirMG995;
    }
  }

  // ==== Stepper Linear Motion ====
  if (now - lastStepper >= intervalStepper) {
    lastStepper = now;
    myStepper.step(stepperDir);
    stepperCount += stepperDir;
    if (stepperCount >= stepsPerRevolution ||
        stepperCount <= -stepsPerRevolution) {
      stepperDir = -stepperDir;
    }
  }
}
