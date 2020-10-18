#include <Arduino.h>

#define LED_red 2
#define button 8
#define buzzer 10

 
void setup ()
{
    Serial.begin(9600);
    pinMode(LED_red, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(button, INPUT);
}

void loop ()
{
    int status = digitalRead(button);

    

    Serial.println(status);
    if(status == 1)
    {
        
        digitalWrite(LED_red, status);
        tone(buzzer, 440);
        delay(1000);
    }
    else
    {
        digitalWrite(LED_red, status);
        noTone(buzzer);
    }

    
}
