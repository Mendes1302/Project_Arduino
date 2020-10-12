#include <Arduino.h>
#include <IRremote.h>

#define pi_IRremote 7
#define tam 3


int vetor_led[tam] = {11, 12 , 13};

IRrecv IRRemote(pi_IRremote);     
decode_results results; 

void setup ()
{
    Serial.begin(9600);     
    IRRemote.enableIRIn();
    for (int i = 0; i < tam; i++)
    {
        pinMode(vetor_led[i], OUTPUT);
    }

}

void loop ()
{
    if(IRRemote.decode(&results))
    {
        int value = results.value;
        switch (value)
        {
        case -23971:
            digitalWrite(vetor_led[0], 1);
            break;
        case 25245:
            digitalWrite(vetor_led[1], 1);
            break;
        case -7651:
            digitalWrite(vetor_led[2], 1);
            break; 
        case 8925:
            digitalWrite(vetor_led[0], 0);
            break;
        case 765:
            digitalWrite(vetor_led[1], 0);
            break;
        case -15811:
            digitalWrite(vetor_led[2], 0);
            break;

        default:
            break;
        }
        IRRemote.resume();
        
    }
    

}
