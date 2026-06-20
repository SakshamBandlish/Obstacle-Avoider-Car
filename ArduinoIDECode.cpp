// ════════════════════════════════════════════════════════════════════════
//   AUTONOMOUS OBSTACLE AVOIDING ROBOT FIRMWARE
//   Compatible with: Real-World Hardware (4-Pin) & Tinkercad (3-Pin)
// ════════════════════════════════════════════════════════════════════════

// ── L293D/L298N Control Pin Config ───────────────────────────────────────
#define EN1  9   // Left Motor Speed Gate (PWM Input)
#define IN1  5   // Left Motor Direction Vector A
#define IN2  6   // Left Motor Direction Vector B
#define IN3  7   // Right Motor Direction Vector A
#define IN4  8   // Right Motor Direction Vector B
#define EN2  10  // Right Motor Speed Gate (PWM Input)

// ── Telemetry & Audio Nodes ──────────────────────────────────────────────
#define SIG_PIN 4  // Transceiver Pin handling both Trigger and Echo
#define BUZZER 11  // Transistor-driven piezo alert line

// ── Behavioral Control System Variables ──────────────────────────────────
#define SAFE_DISTANCE 20  // Critical hazard boundary perimeter zone (cm)
#define MOTOR_SPEED   180  // PWM Output (0-255 scaling) to avoid slippage
#define REVERSE_TIME  500  // Backward actuation duration constraint (ms)
#define TURN_TIME     800  // Pivot duration constraint for 90-degree angle

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(EN1, OUTPUT); pinMode(EN2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  Serial.begin(9600);
  delay(2000); // Guard window to place robot on structural test floor
}

void loop() {
  int distance = getDistance();

  Serial.print("Current Proximity Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < SAFE_DISTANCE) {
    stopMotors();
    beepBuzzer();
    reverseRobot();
    turnRight();
    
    // Auxiliary spatial query scan to ensure the path correction worked
    if (getDistance() <= SAFE_DISTANCE) {
      turnLeft();
    }
  } else {
    moveForward();
  }
}

// ── Telemetry Distance Profiler Function ─────────────────────────────────
long getDistance() {
  // Transmit Phase: Configure pin as output to discharge high sonic burst
  pinMode(SIG_PIN, OUTPUT);
  digitalWrite(SIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SIG_PIN, HIGH);
  delayMicroseconds(10); // Standard trigger configuration window
  digitalWrite(SIG_PIN, LOW);
  
  // Receive Phase: Instantly cycle pin back to high-impedance state to listen
  pinMode(SIG_PIN, INPUT);
  long duration = pulseIn(SIG_PIN, HIGH, 30000); // 30ms internal timeout check
  
  // Convert duration metrics using the constant velocity factor of sound
  return duration * 0.0343 / 2;
}

// ── Actuation Execution Subroutines ──────────────────────────────────────
void moveForward() {
  analogWrite(EN1, MOTOR_SPEED);
  analogWrite(EN2, MOTOR_SPEED);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void reverseRobot() {
  analogWrite(EN1, MOTOR_SPEED);
  analogWrite(EN2, MOTOR_SPEED);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  delay(REVERSE_TIME);
  stopMotors();
}

void turnRight() {
  analogWrite(EN1, MOTOR_SPEED);
  analogWrite(EN2, MOTOR_SPEED);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  // Left Drive Element forward
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); // Right Drive Element backward
  delay(TURN_TIME);
  stopMotors();
}

void turnLeft() {
  analogWrite(EN1, MOTOR_SPEED);
  analogWrite(EN2, MOTOR_SPEED);
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); // Left Drive Element backward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  // Right Drive Element forward
  delay(TURN_TIME);
  stopMotors();
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void beepBuzzer() {
  digitalWrite(BUZZER, HIGH); delay(200);
  digitalWrite(BUZZER, LOW);  delay(100);
  digitalWrite(BUZZER, HIGH); delay(200);
  digitalWrite(BUZZER, LOW);
}