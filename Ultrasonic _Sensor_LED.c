#include <Arduino.h>
#include <Ultrasonic.h>

#define pino_trigger 4
#define pino_echo 5


int led = 10;
Ultrasonic ultrasonic(pino_trigger, pino_echo);
 
void setup ()
{
    Serial.begin(9600);
    pinMode(led, OUTPUT);
}

void loop ()
{
    int Metros;
    Metros = ultrasonic.read();
    Serial.println(Metros);
    if (Metros < 50)
    {
        digitalWrite(led, 1);
    }
    else
    {
        digitalWrite(led, 0);
    }
    delay(1000);

}
