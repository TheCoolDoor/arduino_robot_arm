#include <Servo.h>
#include <Stepper.h>

const int stepsPerRevolution = 2038;

// --- Objects ---
Servo myservo;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

// --- Servo control ---
int servoPos = 0;
int servoDir = 1;              // 1 = forward, -1 = backward
unsigned long lastServoTime = 0;
const unsigned long servoInterval = 15; // ms per degree

// --- Stepper control ---
long stepperPos = 0;
int stepperDir = 1;            // 1 = CW, -1 = CCW
unsigned long lastStepperTime = 0;
const unsigned long stepperInterval = 3; // ms per step

void setup() {
  myservo.attach(6);
  myStepper.setSpeed(10); // RPM
}

void loop() {
  unsigned long now = millis();

  // ===== SERVO (linear sweep) =====
  if (now - lastServoTime >= servoInterval) {
    lastServoTime = now;

    servoPos += servoDir;
    myservo.write(servoPos);

    if (servoPos >= 180 || servoPos <= 0) {
      servoDir = -servoDir; // reverse direction
    }
  }

  // ===== STEPPER (linear rotation) =====
  if (now - lastStepperTime >= stepperInterval) {
    lastStepperTime = now;

    myStepper.step(stepperDir);
    stepperPos += stepperDir;

    if (stepperPos >= stepsPerRevolution ||
        stepperPos <= -stepsPerRevolution) {
      stepperDir = -stepperDir; // reverse direction
    }
  }
}
