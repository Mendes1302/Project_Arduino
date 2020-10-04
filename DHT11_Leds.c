#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <dht.h>
#include <string.h>

#define index 4
#define DHTTYPE DHT11 
#define tam_text 100 

int pino_DHT11 = 2;
int vetor_led[index] = {5, 7, 8, 10};


DHT dht(pino_DHT11, DHTTYPE);


void setup() 
{
  Serial.begin(9600);

  dht.begin();
  for(int i = 0; i < index; i++)
  {
    pinMode(vetor_led[i], OUTPUT);
    digitalWrite(vetor_led[i], 0);
  }
  Serial.println("Temperatura de agora");
  
  }


void loop() 
{
  float Humidity = dht.readHumidity();
  float Temperature = dht.readTemperature();
  char text_Temperature[tam_text];
  char text_Humidity[tam_text];

  //isnan = É numero
  if(isnan(Humidity)||isnan(Humidity))
  {
    Serial.println("FALHA!!!");
  }
  else
  {
    if(Temperature)
    {
      if(Temperature >= 30)
      {
        Serial.println("Alerta VERMELHO temperatura acima de 30*C");
        digitalWrite(vetor_led[3], 1);//liga vermelho
        digitalWrite(vetor_led[1], 0);//liga verde
      }else
      {
        Serial.println("Temperatura NORMAL alerta verde");
        digitalWrite(vetor_led[1], 1);//liga verde
        digitalWrite(vetor_led[3], 0);//liga vermelho
      }
    }
    if (Humidity)
    {
      if (Humidity > 50)
      {
        Serial.println("Humidade relativa do ar NORMAL alerta azul");
        digitalWrite(vetor_led[0], 1);//liga azul
        digitalWrite(vetor_led[2], 0);//liga amarelo 
      }    
      else
      {
        Serial.println("Alerta AMARELO Humidade relativa do ar abaixo de 50%");
        digitalWrite(vetor_led[2], 1);//liga amarelo  
        digitalWrite(vetor_led[0], 0);//liga azul      
      }
      
    }
    
    /*snprintf(text_Humidity, 100, "Umidade relativa do ar agora: %i", Humidity);
    snprintf(text_Temperature, 100, "Temperatura agora: %i *C", Temperature);*/
    
  Serial.print("Umidade relativa do ar agora:"); Serial.print(Humidity); Serial.println("%");
    Serial.print("Temperatura agora:"); Serial.print(Temperature); Serial.println("*C");
    
    

    delay(10000);
  }
  

}
