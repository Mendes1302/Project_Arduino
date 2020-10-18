#include <Arduino.h>

#define LED_red 2
#define button 8

 
void setup ()
{
    Serial.begin(9600);
    pinMode(LED_red, OUTPUT);
    pinMode(button, INPUT);
}

void loop ()
{
    int status = digitalRead(button);

    Serial.println(status);
    if(status == 1)
    {
        Serial.println("fgdf");
        digitalWrite(LED_red, status);
    }else
    {
        digitalWrite(LED_red, status);
    }

    
}
