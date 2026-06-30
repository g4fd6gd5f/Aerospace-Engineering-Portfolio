#include <Servo.h>

const int trigPin = 2;
const int echoPin = 9;
const int servoPin = 12;

long duration;
int distance;

Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop() {
  for (int angle = 15; angle <= 165; angle++) {
    myServo.write(angle);
    delay(30);

    distance = calculateDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.println(".");
  }

  for (int angle = 165; angle >= 15; angle--) {
    myServo.write(angle);
    delay(30);

    distance = calculateDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.println(".");
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return 999;
  }

  distance = duration * 0.034 / 2;
  return distance;
}