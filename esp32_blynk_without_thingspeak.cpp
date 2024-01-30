#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLSJRdJ75T"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "Y3W15vPCDPyv9mIVKRbQc-KB-eNSytxS"


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Servo.h>

/*Servo motor responsible for opening the compartment*/
Servo petGate;
int gateStart = 45;
int gateEnd = 120;
int gateOpenTime = 200;

char auth[] = "Y3W15vPCDPyv9mIVKRbQc-KB-eNSytxS";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YOUR WIFI SSID";
char pass[] = "YOUR WIFI PASSWORD";

BLYNK_WRITE(V0)
{
  petGate.write(gateEnd);
  delay(gateOpenTime);
  petGate.write(gateStart);
}

BLYNK_WRITE(V1)
{
  for(int i=0;i<2;i++)
  {
    petGate.write(gateEnd);
    delay(gateOpenTime);
    petGate.write(gateStart);
    delay(gateOpenTime);
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  petGate.attach(13, OUTPUT);
  petGate.write(gateStart);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
