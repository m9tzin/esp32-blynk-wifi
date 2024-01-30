#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLSJRdJ75T"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "Y3W15vPCDPyv9mIVKRbQc-KB-eNSytxS"


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Servo.h>
#include <ThingSpeak.h>

/*Servo motor responsible for opening the compartment*/
Servo petGate; 
int gateStart = 45;
int gateEnd = 120;
int gateOpenTime = 200;
int active=0;

/* Complete with your data, Channel ID, API Key */
unsigned long channelID = YOUR THINGSPEAK CHANNELID;
const char* WriteAPIKey ="YOUR THINGSPEAK API KEY";
WiFiClient client;

char auth[] = "YOUR CHAR AUTH (BLYNK)";
char ssid[] = "YOUR WIFI SSID";
char password[] = "YOUR WIFI PASSWORD";


BLYNK_WRITE(V0)
{
  delay(800);
  active=1;
  readData();	
  ThingSpeak.writeFields(channelID,WriteAPIKey);
  
  petGate.write(gateEnd);
  delay(gateOpenTime);
  petGate.write(gateStart);

}

BLYNK_WRITE(V1)
{
  for(int i=0;i<2;i++)
  {
    delay(800);
    active=2;
    readData();	
    ThingSpeak.writeFields(channelID,WriteAPIKey);
    
    petGate.write(gateEnd);
    delay(gateOpenTime);
    petGate.write(gateStart);
    delay(gateOpenTime);
    
  }
  
}

void setup()
{
	Serial.begin(9600);
	delay(1000);
	WiFi.begin(ssid,password);
	while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado no WiFi");
  ThingSpeak.begin(client);
  delay(5000);
  // Debug console
  Serial.begin(9600);
  petGate.attach(13, OUTPUT);
  petGate.write(gateStart);
  Blynk.begin(auth, ssid, password);
}

void loop()
{
  Blynk.run();
}
void readData(){

  /*Thingspeak response*/
  ThingSpeak.setField(1, active);
  
}
