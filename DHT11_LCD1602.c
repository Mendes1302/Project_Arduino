#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <dht.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHTTYPE DHT11 
int pino_DHT11 = 8;

DHT dht(pino_DHT11, DHTTYPE);

void setup()
{
	lcd.begin(16, 2);
	dht.begin();
	
}

void loop()
{
	int Humidity = dht.readHumidity();
  	int Temperature = dht.readTemperature();

	if(isnan(Humidity)||isnan(Humidity))
	{
		Serial.println("FALHA!!!");
	}
	else
	{
		lcd.print("Atualizando em:");
		lcd.setCursor(0,1);
		for(int i = 1; i < 4; i++)
		{
			lcd.print(i);lcd.print(" ");
			lcd.setCursor(0,1);
			delay(1000);
		}	
		lcd.clear();
		lcd.print("Temperatura:");lcd.print(Temperature);lcd.print("C");
		lcd.setCursor(0,1);
		lcd.print("Humidade:");lcd.print(Humidity);lcd.print("%");
		delay(5000);
		lcd.clear();
		
		
	}
	
}
