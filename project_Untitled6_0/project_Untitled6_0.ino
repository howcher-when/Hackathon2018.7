#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeOrion.h>

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
Servo servo_3_1;
MePort port_3(3);
MeJoystick joystick_7(7);
MeRGBLed rgbled_6(6, 4);



void setup(){
    servo_3_1.attach(port_3.pin1());
    servo_3_1.write(45);
    
}

void loop(){
    
    while(!(((joystick_7.read(1)) + (joystick_7.read(2))) > (0  )))
    {
        _loop();
    }
    _delay(1);
    servo_3_1.write(135);
    _delay(1);
    for(int __i__=0;__i__<10;++__i__)
    {
        rgbled_6.setColor(0,255,0,0);
        rgbled_6.show();
        _delay(0.5);
        rgbled_6.setColor(0,0,150,150);
        rgbled_6.show();
        _delay(0.5);
        buzzerOn();
    _delay(0.2);
    buzzerOff();
    _delay(0.2);
    }
    rgbled_6.setColor(0,0,0,0);
    rgbled_6.show();
    
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
}

