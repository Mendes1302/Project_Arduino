#include <Arduino.h>


#define tam 5
#define Apotenciometro A0

int vetor_LED [tam] = {2, 3, 4, 6, 7};



void setup ()
{
    Serial.begin(9600);
    for (int i = 0; i < tam; i++)
    {
        pinMode(vetor_LED[i], OUTPUT);
        digitalWrite(vetor_LED[i], 0);
    }
}

void loop ()
{
    int status = analogRead(Apotenciometro);
    status = map(status, 0, 1023, 0, 255);
    Serial.println(status);

   
    
    if((status < 20) || status == 0)
    {
        analogWrite(vetor_LED[0], 250);
    }
    if ((status < 50 && status > 19) || status == 0)
    {
        analogWrite(vetor_LED[1], status);
    }
    if ((status < 100 && status > 49) || status == 0)
    {
        analogWrite(vetor_LED[2], status);
    }
    if ((status < 150 && status > 99) || status == 0)
    {
        analogWrite(vetor_LED[3], status);
    }
    if ((status < 300 && status > 149) || status == 0)
    {
        analogWrite(vetor_LED[4], status);
    }
      
        

}
