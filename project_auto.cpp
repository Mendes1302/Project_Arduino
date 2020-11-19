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

int array_LED[tam] = {18, 19, 21};

DHT dht(DHTPIN, DHTTYPE);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

char ssid[] = "Overload";
char password[] = "1010FC216810";
int Bot_mtbs = 1000;
long Bot_lasttime;
String id, text;
unsigned long tempo;

void setup() 
{
	/*Serial.begin(9600);
	Serial.print("Connecting Wifi: ");
	Serial.println(ssid);*/

	
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	dht.begin();

	
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(500);
	}
	
	/*Serial.println("");
	Serial.println("WiFi connected");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());*/

	for(int i = 0; i < tam; i++)
	{
		pinMode(array_LED[i], OUTPUT);
		digitalWrite(array_LED[i], 0);
	}

}

void loop() 
{
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	if (isnan(h) || isnan(t)) {
		//Serial.println(F("Failed to read from DHT sensor!"));
		return;
	}
		
	if (millis() - tempo > 2000)  
	{
		if (WiFi.status() != WL_CONNECTED)   {
		WiFi.begin("ssid", "password");
		delay(2000);
		}
		
		String response = "";
		tempo = millis();//Reseta o tempo
	
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
					response = "Bem-vindo \xF0\x9F\x98\x8E, comandos disponíveis: \n"; 
					response += "/Temperature\xE2\x98\x81\n";
					response += "/Humidity\xE2\x98\x94 \n";
					response += "/Both\xE2\x98\x81 \xE2\x98\x94 \n";
					response += "/OFFALL\n";
					response += "/ONWHITE\n";
					response += "/ONBLUE\n";
					response += "/ONRED\n";
					response += "/ONGREEN\n";
					response += "/ONPINK\n";
					response += "/ONYELLOW\n";
					response += "/ONTURQUOISE\n";
					response += "/ONBLINK\n";
					bot.sendMessage(id, response, "");
				}

				else if (text.indexOf("HUMIDITY") > -1)    
				{
					if (h > 70 || h < 40)
					{
						response = "Humidade relativa do ar: " + String(h) + "%.\xF0\x9F\x8D\xB6";
					}
					else
					{
						response = "Humidade relativa do ar: " + String(h) + "%.\xF0\x9F\x91\x8D";
					}
					
					bot.sendMessage(id, response , "");
				}	
				else if (text.indexOf("TEMPERATURE") > -1)    
				{
					if (t > 25)
					{
						response = "Temperatura agora: " + String(t) + "*C.\xE2\x98\x80";
					}
					else if (t < 15)
					{
						response = "Temperatura agora: " + String(t) + "*C.\xE2\x9D\x84";
					}
					else
					{
						response = "Temperatura agora: " + String(t) + "*C.\xF0\x9F\x91\x8D";						
					}
					
						
					bot.sendMessage(id, response, "");
				}
				else if (text.indexOf("BOTH") > -1)    
				{
					response = "Temperatura agora: " + String(t) + "*C.\n";
					response += "Humidade relativa do ar: " + String(h) + "%.";
					bot.sendMessage(id, response, "");
				}	
				else if (text.indexOf("OFFALL") > -1)    
				{
					for(int i = 0; i < 3; i++)
					{
						digitalWrite(array_LED[i], 0);
					}
					response = "LED branco desligado\n";
					bot.sendMessage(id, response, "");
				}
				else if (text.indexOf("ONWHITE") > -1)    
				{
					for(int i = 0; i < 3; i++)
					{
						digitalWrite(array_LED[i], 1);
					}
					response = "LED azul desligado\n";
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
				else if (text.indexOf("ONBLINK") > -1)    
				{
					
					for(int i = 0; i < 3; i++)
					{
						digitalWrite(array_LED[i], 1);
						digitalWrite(array_LED[i], 0);

					}
					response = "LED blink ligado\xF0\x9F\x92\xA1\n";
					bot.sendMessage(id, response, "");
				}
				else   
				{
					bot.sendMessage(id, "Comando Invalido 	\xF0\x9F\x9A\xAB", "");
				}
			}
			else
			{
				bot.sendMessage(id, "ACESSO NEGADO!!\xE2\x9D\x8C", "");
			}
		}
	}
}
