/*
 * ============================================================
 * Line Follower Robot Using IR Sensors
 * ============================================================
 * University  : University of Central Punjab (UCP)
 * Course      : Robotics Design Lab - 1 (REE220)
 * Instructor  : Dr. Nabeel Khalid
 * Session     : Spring 2025
 * Authors     : Muhammad Mamoon  (L1F23BSRI0014)
 *               Ali Ahmar Awan  (L1F23BSRI0013)
 *               Asad Ali        (L1F23BSRI0024)
 * ============================================================
 *
 * Description:
 * Autonomous line follower robot using a 5-channel TCRT5000
 * IR sensor array. Arduino Nano reads sensor states and drives
 * two N20 DC gear motors via L298N motor driver.
 *
 * Sensor Logic:
 *   LOW  = Black line detected (IR absorbed)
 *   HIGH = White surface (IR reflected)
 *
 * Movement Decisions:
 *   S2=0, S3=1, S4=0         → Forward
 *   S1=0, S2=1, S3=1         → Slight Left
 *   S3=1, S4=1, S5=0         → Slight Right
 *   S1=1, S2=1               → Sharp Left
 *   S4=1, S5=1               → Sharp Right
 *   All sensors = 0          → Stop (line lost)
 *
 * Pin Map:
 *   IR Sensors : S1=A0, S2=A1, S3=A2, S4=A3, S5=A4
 *   Left Motor : IN1=D9, IN2=D8, ENA=D10 (PWM)
 *   Right Motor: IN3=D7, IN4=D6, ENB=D5  (PWM)
 * ============================================================
 */

// ── Motor Driver Pins ─────────────────────────────────────────
const int IN1 = 9;    // Left motor direction A
const int IN2 = 8;    // Left motor direction B
const int IN3 = 7;    // Right motor direction A
const int IN4 = 6;    // Right motor direction B
const int ENA = 10;   // Left motor speed (PWM)
const int ENB = 5;    // Right motor speed (PWM)

// ── IR Sensor Pins ────────────────────────────────────────────
const int S1 = A0;    // Far Left sensor
const int S2 = A1;    // Center Left sensor
const int S3 = A2;    // Center sensor
const int S4 = A3;    // Center Right sensor
const int S5 = A4;    // Far Right sensor

// ── Speed Setting (0–255) ─────────────────────────────────────
int speedMotor = 100; // Adjust for surface and motor characteristics

// ── Setup ─────────────────────────────────────────────────────
void setup() {
  // Motor driver pins as output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Sensor pins as input
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  Serial.begin(9600);
  Serial.println("Line Follower Robot — Ready");
}

// ── Main Loop ─────────────────────────────────────────────────
void loop() {
  // Read all 5 IR sensors
  int s1 = digitalRead(S1);
  int s2 = digitalRead(S2);
  int s3 = digitalRead(S3);
  int s4 = digitalRead(S4);
  int s5 = digitalRead(S5);

  // Print sensor states for debugging
  Serial.print("S1:"); Serial.print(s1);
  Serial.print(" S2:"); Serial.print(s2);
  Serial.print(" S3:"); Serial.print(s3);
  Serial.print(" S4:"); Serial.print(s4);
  Serial.print(" S5:"); Serial.println(s5);

  // ── Decision Logic ──────────────────────────────────────────

  if (s2 == 0 && s3 == 1 && s4 == 0) {
    // Line centered → go straight
    forward();

  } else if (s1 == 0 && s2 == 1 && s3 == 1) {
    // Line slightly to the left
    slightLeft();

  } else if (s3 == 1 && s4 == 1 && s5 == 0) {
    // Line slightly to the right
    slightRight();

  } else if (s1 == 1 && s2 == 1) {
    // Line far left → sharp left turn
    sharpLeft();

  } else if (s4 == 1 && s5 == 1) {
    // Line far right → sharp right turn
    sharpRight();

  } else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 0) {
    // No line detected → stop
    stopMotors();

  } else {
    // Default: keep going forward
    forward();
  }
}

// ── Motor Control Functions ───────────────────────────────────

// Move both motors forward at full speed
void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
}

// Slight left: left motor slows/reverses, right motor full speed
void slightLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);  // Left motor slow/reverse
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);   // Right motor forward
  analogWrite(ENA, speedMotor / 2);
  analogWrite(ENB, speedMotor);
}

// Slight right: right motor slows/reverses, left motor full speed
void slightRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);   // Left motor forward
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);  // Right motor slow/reverse
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor / 2);
}

// Sharp left: left reverses, right forward — both full speed
void sharpLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
}

// Sharp right: right reverses, left forward — both full speed
void sharpRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
}

// Stop all motors
void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
