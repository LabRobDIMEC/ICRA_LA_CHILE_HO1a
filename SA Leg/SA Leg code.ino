//This approach uses a Nema17 Stepper motor with an EasyDriver A3867, controlled with Arduino Uno
//The speed and direction are of the motor controlled with a potentiometer
#define STEP_PIN 3
#define DIR_PIN 2
#define POT_PIN A0

const int deadZoneLow = 500;
const int deadZoneHigh = 524;

unsigned long lastStepTime = 0;
unsigned int stepInterval = 2000; // default
bool motorRunning = false;

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
}

void loop() {
  int potValue = analogRead(POT_PIN);

  if (potValue >= deadZoneLow && potValue <= deadZoneHigh) {
    motorRunning = false;
    return;
  }

  motorRunning = true;

  // Set direction
  bool dir = potValue > deadZoneHigh;
  digitalWrite(DIR_PIN, dir ? HIGH : LOW);

  // Map pot to interval: faster = smaller interval
  int speedVal = dir ? (potValue - deadZoneHigh) : (deadZoneLow - potValue);
  stepInterval = map(speedVal, 0, 500, 3000, 400); // adjust to your needs

  // Non-blocking step pulse
  unsigned long now = micros();
  if (now - lastStepTime >= stepInterval) {
    lastStepTime = now;
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(2); // Short pulse
    digitalWrite(STEP_PIN, LOW);
  }
}
