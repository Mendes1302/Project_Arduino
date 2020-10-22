#include <Arduino.h>


#define tam 10

int eixo_x = A0;
int eixo_y = A1;
int button = 3;
int vetor_LED [tam] = {2, 4, 5, 6, 8, 9, 10, 11, 12, 13};
int update_status;



void setup ()
{
    Serial.begin(9600);
    for (int i = 0; i < tam; i++)
    {
        pinMode(vetor_LED[i], OUTPUT);
        digitalWrite(vetor_LED[i], 0);
    }
    pinMode(button, INPUT_PULLUP);
}

void loop ()
{
    int status = digitalRead(button);
    Serial.print("status: ");Serial.println(status);
    Serial.print("x:");Serial.println(analogRead(eixo_y));
    Serial.print("y:");Serial.println(analogRead(eixo_x));
    if (analogRead(eixo_y) == 0)
    {
       for(int i = 0; i < tam; i++)
        {
            digitalWrite(vetor_LED[i], 1);
            delay(50);
        } 
         for(int i = 0; i < tam; i++)
        {
            digitalWrite(vetor_LED[i], 0);
            delay(50);
        }
    }
    
    if (analogRead(eixo_y) == 1023)
    {
        for(int i = (tam-1); i >= 0; i--)
        {
            digitalWrite(vetor_LED[i], 1);
            delay(50);
        }
        for(int i = (tam-1); i >= 0; i--)
        {
            digitalWrite(vetor_LED[i], 0);
            delay(50);
        }
    }
    if (digitalRead(button) == 0)
    {
        for(int i = 0; i < tam; i++)
        {
            digitalWrite(vetor_LED[i], 1);
            delay(50);
        }
        for(int i = 0; i < tam; i++)
        {
            digitalWrite(vetor_LED[i], 0);
            delay(50);
        }
    }            

    delay(50);
    
}
