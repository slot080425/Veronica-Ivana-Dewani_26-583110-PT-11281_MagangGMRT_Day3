/*
 * Nama: Veronica Ivana Dewani
 * NIM: 26/583110/PT/11281
 */

#include <ESP32Servo.h>

#define PIN_SDA 21
#define PIN_SCL 22
#define PIN_PIR 13

#define PIN_SERVO_1 2
#define PIN_SERVO_2 4
#define PIN_SERVO_3 5
#define PIN_SERVO_4 18
#define PIN_SERVO_5 19

Servo servo1, servo2, servo3, servo4, servo5;

unsigned long yawberhenti = 0;
float yawsebelumnya = 0.0;
bool yawgerak = false;
bool yawbersiaplah = false;

float roll_deg = 0.0;
float pitch_deg = 0.0;
float yaw_deg = 45.0;

int hitungPWM(float derajat) {
  return 1500 + (int)(derajat * (500.0 / 90.0));
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_PIR, INPUT);
  
  servo1.attach(PIN_SERVO_1, 1000, 2000);
  servo2.attach(PIN_SERVO_2, 1000, 2000);
  servo3.attach(PIN_SERVO_3, 1000, 2000);
  servo4.attach(PIN_SERVO_4, 1000, 2000);
  servo5.attach(PIN_SERVO_5, 1000, 2000);
  
  Serial.println("BNO055 & PIR aktif");
}

void loop() {
  unsigned long sekarang = millis();
  bool deteksiPIR = digitalRead(PIN_PIR);

  if (deteksiPIR == HIGH) {
    int targetPIR = hitungPWM(45.0);
    servo1.writeMicroseconds(targetPIR);
    servo2.writeMicroseconds(targetPIR);
    servo3.writeMicroseconds(targetPIR);
    servo4.writeMicroseconds(targetPIR);
    servo5.writeMicroseconds(targetPIR);
    return;
  }

  roll_deg = 30.0; 
  pitch_deg = -20.0; 
  
  int pwmRoll = hitungPWM(-roll_deg);
  servo1.writeMicroseconds(pwmRoll);
  servo2.writeMicroseconds(pwmRoll);

  int pwmPitch = hitungPWM(pitch_deg);
  servo3.writeMicroseconds(pwmPitch);
  servo4.writeMicroseconds(pwmPitch);

  if (abs(yaw_deg - yawsebelumnya) > 0.5) {
    yawgerak = true;
    yawbersiaplah = false;
    servo5.writeMicroseconds(hitungPWM(yaw_deg));
    yawsebelumnya = yaw_deg;
  } else {
    if (yawgerak) {
      yawberhenti = sekarang;
      yawgerak = false;
      yawbersiaplah = true;
    }
    
    if (yawbersiaplah && (sekarang - yawberhenti >= 1000)) {
      servo5.writeMicroseconds(1500); 
      yawbersiaplah = false;
    }
  }

  Serial.print("S1_S2(Roll): "); Serial.print(pwmRoll);
  Serial.print(" us | S3_S4(Pitch): "); Serial.print(pwmPitch);
  Serial.println(" us");
  
  delay(100);
}