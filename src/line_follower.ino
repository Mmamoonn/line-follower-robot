// ── Motor Driver Pins ─────────────────────────────────────────
const int IN1 = 9;   
const int IN2 = 8;   
const int IN3 = 7;   
const int IN4 = 6;   
const int ENA = 10;  
const int ENB = 5;   

// ── IR Sensor Pins ────────────────────────────────────────────
const int S1 = A0;   
const int S2 = A1;    
const int S3 = A2;    
const int S4 = A3;    
const int S5 = A4;    

// ── Speed Setting (0–255) ─────────────────────────────────────
int speedMotor = 100; 

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

void loop() {

  int s1 = digitalRead(S1);
  int s2 = digitalRead(S2);
  int s3 = digitalRead(S3);
  int s4 = digitalRead(S4);
  int s5 = digitalRead(S5);

  Serial.print("S1:"); Serial.print(s1);
  Serial.print(" S2:"); Serial.print(s2);
  Serial.print(" S3:"); Serial.print(s3);
  Serial.print(" S4:"); Serial.print(s4);
  Serial.print(" S5:"); Serial.println(s5);

  // ── Decision Logic ──────────────────────────────────────────

  if (s2 == 0 && s3 == 1 && s4 == 0) {
    forward();

  } else if (s1 == 0 && s2 == 1 && s3 == 1) {
    slightLeft();

  } else if (s3 == 1 && s4 == 1 && s5 == 0) {
    slightRight();

  } else if (s1 == 1 && s2 == 1) {
    sharpLeft();

  } else if (s4 == 1 && s5 == 1) {
    sharpRight();

  } else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 0) {
    stopMotors();

  } else {
    forward();
  }
}

void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
}

void slightLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);  
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);   
  analogWrite(ENA, speedMotor / 2);
  analogWrite(ENB, speedMotor);
}

void slightRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);   
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); 
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor / 2);
}

void sharpLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
}

void sharpRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
