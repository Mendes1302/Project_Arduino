#include <Arduino.h>
#include <Servo.h>


#define pinServo 9
#define Apotenciometro A0

Servo servo;

void setup ()
{
    Serial.begin(9600);
    servo.attach(pinServo);
}

void loop ()
{
    int angulo = analogRead(Apotenciometro);
    Serial.println(angulo);
    angulo = map(angulo, 0, 1023, 0, 179);

    servo.write(angulo);
    
    delay(10);

}
