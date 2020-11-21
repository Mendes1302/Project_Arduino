#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <dht.h>
#include <string.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define tam 3
#define DHTPIN 4
#define DHTTYPE DHT11
#define BOTtoken "1478659660:AAF-JKWIfED5_V-BQsLqW8i4bxKi7SCvsQU"
#define CHAT_ID "816137990"

void STS(String id);
void LED(String id);
void SENSOR_DHT11(String id);
void START(String id);
void COMAND_FAIL(String id);

DHT dht(DHTPIN, DHTTYPE);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int array_LED[tam] = {18, 19, 21};
char ssid[] = "Overload";
char password[] = "1010FC216810";
int Bot_mtbs = 1000;
long Bot_lasttime;
String id, text;
unsigned long tempo = 0;



void SENSOR_DHT11 (String id)
{
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	if (isnan(h) || isnan(t)) 
	{
		Serial.println(F("Failed to read from DHT sensor!"));
		return;
	}

	String response = "";
	if (h > 70 || h < 40)
	{
		response += "\nHumidade relativa do ar: " + String(h) + "%.\xF0\x9F\x8D\xB6";
	}	
	if (t > 25)
	{
		response += "\nTemperatura agora: " + String(t) + "°C.\xE2\x98\x80";
	}
	if (t < 15)
	{
		response += "\nTemperatura agora: " + String(t) + "°C.\xE2\x9D\x84";
	}
	if(h <= 70 && h >= 40)
	{
		response += "\nHumidade relativa do ar: " + String(h) + "%.\xF0\x9F\x91\x8D";
	}
	if(t >= 15 && t <= 25)
	{
		response += "\nTemperatura agora: " + String(t) + "°C.\xF0\x9F\x91\x8D";
	}
	if ((t >= 15 && t <= 25) && (h <= 70 && h >= 40))
	{
		response += "\nHumidade relativa do ar: " + String(h) + "%.\xF0\x9F\x91\x8D";
		response += "\nTemperatura agora: " + String(t) + "°C.\xF0\x9F\x91\x8D";						
	}
	bot.sendMessage(id, response, "");
}
void LED(String id)
{	
	unsigned long time = 0;
	int controle = 0;
	String response = "";
	response += "COMANDOS PARA LED:\n\n";
	response += "/OFFALL\n";
	response += "/ONWHITE\n";
	response += "/ONBLUE\n";
	response += "/ONRED\n";
	response += "/ONGREEN\n";
	response += "/ONPINK\n";
	response += "/ONYELLOW\n";
	response += "/ONTURQUOISE\n\n";
	response += "COMANDOS PARA SAIR:\n\n";
	response += " - /START\n";
	bot.sendMessage(id, response, "");
	while(1)
	{
		if (millis() - time > 1000)  
		{
			time = millis();
		
			int newmsg = bot.getUpdates(bot.last_message_received+1);
			for (int i=0; i<newmsg; i++)
			{
				text = bot.messages[i].text;
				text.toUpperCase();

				if (text.indexOf("OFFALL") > -1)  
				{  		
					for(int i = 0; i < 3; i++)
					{
						digitalWrite(array_LED[i], 0);
					}
					response = "LED´s desligados\n";
					bot.sendMessage(id, response, "");
				}
				else if (text.indexOf("ONWHITE") > -1)    
				{
					for(int i = 0; i < 3; i++)
					{
						digitalWrite(array_LED[i], 1);
					}
					response = "LED branco desligado\n";
					bot.sendMessage(id, response, "");
				}
				else if (text.indexOf("ONBLUE") > -1)    
				{
					digitalWrite(array_LED[2], 1);
					response = "LED azul ligado\xF0\x9F\x92\xA1\n";
					bot.sendMessage(id, response, "");
				}
				else if (text.indexOf("ONRED") > -1)    
				{
					digitalWrite(array_LED[0], 1);
					response = "LED vermelho ligado\xF0\x9F\x92\xA1\n";
					bot.sendMessage(id, response, "");
				}
				else if (text.indexOf("ONGREEN") > -1)    
				{
					digitalWrite(array_LED[1], 1);
					response = "LED verde ligado\xF0\x9F\x92\xA1\n";
					bot.sendMessage(id, response, "");
				}
				else if (text.indexOf("ONPINK") > -1)    
				{
					digitalWrite(array_LED[0], 1);
					digitalWrite(array_LED[2], 1);
					response = "LED rosa ligado\xF0\x9F\x92\xA1\n";
					bot.sendMessage(id, response, "");
				}
				else if (text.indexOf("ONYELLOW") > -1)    
				{
					digitalWrite(array_LED[0], 1);
					digitalWrite(array_LED[1], 1);
					response = "LED amarelo ligado\xF0\x9F\x92\xA1\n";
					bot.sendMessage(id, response, "");
				}
				else if (text.indexOf("ONTURQUOISE") > -1)    
				{
					digitalWrite(array_LED[2], 1);
					digitalWrite(array_LED[1], 1);
					response = "LED turquesa ligado\xF0\x9F\x92\xA1\n";
					bot.sendMessage(id, response, "");
				}
				else if (text.indexOf("START") > -1)    
				{
					controle = 1;
				}
				else
				{
					COMAND_FAIL(id);
				}
			}
		}
		if(controle == 1)
		{
			START(id);
			break;
		}
	}
}
void STS(String id)
{
	String response = "";
	int status_LED;
	response += "STATUS:\n\n";
	response += "STATUS do DHT11:\n";
	if (!isnan(dht.readHumidity()) || !isnan(dht.readTemperature())) 
	{
		response += "  DHT sensor OK!\xE2\x9C\x85\n";
	}
	if (isnan(dht.readHumidity()) || isnan(dht.readTemperature())) 
	{
		Serial.println("ok");
		response += "  DHT sensor FAIL!\xF0\x9F\x9A\xA8\n";
	}
	response += "\nSTATUS do LED:\n";
	for (int i = 0; i < tam; i++)
	{
		status_LED = digitalRead(array_LED[i]);
		if (status_LED == 1)
		{
			if(i == 0)
			{
				response += "  LED VERMELHO LIGADO\n";
			}
			if(i == 1)
			{
				response += "  LED VERDE LIGADO\n";
			}
			if(i == 2)
			{
				response += "  LED AZUL LIGADO\n";
			}
		}
		else
		{
			if(i == 0)
			{
				response += "  LED VERMELHO DESLIGADO\n";
			}
			if(i == 1)
			{
				response += "  LED VERDE DESLIGADO\n";
			}
			if(i == 2)
			{
				response += "  LED AZUL DESLIGADO\n";
			}
		}	
	}
	bot.sendMessage(id, response, "");
}


void START(String id)
{
	String response = "";
	response = "Bem-vindo \xF0\x9F\x98\x8E, comandos disponíveis: \n"; 
	response += "/HUMIDADE_TEMPERATURE\xE2\x98\x81\xE2\x98\x94\n";
	response += "/LED\xF0\x9F\x92\xA1\n";
	response += "/STATUS\xF0\x9F\x93\x84\n";
	bot.sendMessage(id, response, "");
}
void COMAND_FAIL(String id)
{
	String response = "";
	bot.sendMessage(id, "Comando Invalido\xF0\x9F\x9A\xAB", "");
}


void setup() 
{
	Serial.begin(9600);
	Serial.print("Connecting Wifi: ");
	Serial.println(ssid);

	
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	dht.begin();

	
	while (WiFi.status() != WL_CONNECTED) 
	{
		Serial.print(".");
		delay(500);
	}
	
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	for(int i = 0; i < tam; i++)
	{
		pinMode(array_LED[i], OUTPUT);
		digitalWrite(array_LED[i], 0);
	}

}
void loop() 
{	
	String response = "";
	if (millis() - tempo > 2000)  
	{
		if (WiFi.status() != WL_CONNECTED)   
		{
			WiFi.begin("ssid", "password");
			delay(2000);
		}

		tempo = millis();
		int newmsg = bot.getUpdates(bot.last_message_received + 1);
	
		for (int i = 0; i < newmsg; i++)  
		{
			id = bot.messages[i].chat_id;
			if(id == CHAT_ID)
			{
				text = bot.messages[i].text;
				text.toUpperCase();
		
				if (text.indexOf("START") > -1)    
				{
					START(id);
				}

				else if (text.indexOf("HUMIDADE_TEMPERATURE") > -1)    
				{
					SENSOR_DHT11(id);
				}	
				else if (text.indexOf("LED") > -1)    
				{
					LED(id);
				}
				else if (text.indexOf("STATUS") > -1)    
				{
					STS(id);
				}
				else   
				{
					COMAND_FAIL(id);
				}
			}
			else
			{
				bot.sendMessage(id, "ACESSO NEGADO!!\xE2\x9D\x8C", "");
			}
		}
	}
}
