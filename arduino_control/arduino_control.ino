//#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeOrion.h>

#define buttonPin  2
#define ledPin 13
#define PIN_SERVO 3
const double angle_rad = PI/180.0;
const double angle_deg = 180.0/PI;
Servo servo_3_1;
MePort port_3(3);
MeJoystick joystick_7(7);
MeRGBLed rgbled_6(6, 4);
bool opened;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  servo_3_1.attach(port_3.pin1());
  servo_3_1.write(135);
  opened = true;
}

void loop() {
  if(opened) {
    if(!finger_test()) {
      servo_3_1.write(45);
      delay(2000);
      alarm_close();
      opened = false;
    }
  } else {
    if(finger_test() && cv_test()) {
      servo_3_1.write(135);
      delay(1000);
      alarm_open();
      opened = true;
    }
  }
}

void alarm_open() {
  /*for(int i = 0; i < 10; ++i) {
    //rgbled_6.setColor(0,255,0,0);
    //rgbled_6.show();
    delay(500);
    //rgbled_6.setColor(0,0,150,150);
    //rgbled_6.show();
    delay(500);
    buzzerOn();
    delay(200);
    buzzerOff();
    delay(200);
  }*/
}

void alarm_close() {
  rgbled_6.setColor(0,0,0,0);
  rgbled_6.show();
}

bool finger_test() {
  if(!(((joystick_7.read(1)) + (joystick_7.read(2))) > (0))) {
    return false;
  } else {
    return true;
  }
}

bool cv_test() {
  char ch = Serial.read();
  //delay(100);
  if(ch == '1') {
    rgbled_6.setColor(0,255,0,0);
    rgbled_6.show();
    return true;
  } else {
    rgbled_6.setColor(0,0,0,0);
    rgbled_6.show();
    return false;
  }
}

