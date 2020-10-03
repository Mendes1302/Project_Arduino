#include <Arduino.h>

#define index 4
int vetor[index] = {2, 4, 8, 10};


void setup() 
{
  for(int i = 0; i < index; i++)
  {
    pinMode(vetor[i], OUTPUT);
  }
}


void loop() 
{
 for(int i = 0; i < index; i++)
 {
   digitalWrite(vetor[i], 1);
   delay(50*i+100);
 }
 for(int i = 0; i < index; i++)
 {
   digitalWrite(vetor[i], 0);
   if (i == (index-1))
   {
     delay(300);
   }
 }
}
