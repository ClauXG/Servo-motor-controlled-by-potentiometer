#include <ESP32Servo.h>

Servo myservo;

int potPin = 34;
int servoPin = 18;
int signalPin = 32;

void setup() {
    Serial.begin(115200);

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    myservo.setPeriodHertz(50);
    myservo.attach(servoPin, 500, 2400);
    pinMode(signalPin, OUTPUT);
}

void loop() {
    int potValue = analogRead(potPin);
    float potPercentage = (potValue / 4095.0) * 100;
    
    int servoPos;
    if (potPercentage <= 30) {
        servoPos = map(potValue, 0, 4095 * 0.3, 0, 90);
    } else {
        servoPos = 90;
    }
    myservo.write(servoPos);

    if (servoPos == 90) {
        digitalWrite(signalPin, HIGH);
        Serial.println("Servo at 90 deg, ratata signal on");
    } else{
      digitalWrite(signalPin, LOW);
    }
}
