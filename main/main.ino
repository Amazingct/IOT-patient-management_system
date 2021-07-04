#include "Ubidots.h"
#include <ESP8266WiFi.h>
const char* UBIDOTS_TOKEN = "BBFF-YRpT6QwkDeCAjElEUd9NBLD0VqZAKb";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "project_dra";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "project_dra";      // Put here your Wi-Fi password 
String upload;
bool online = 1;
long int counter = 0;
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

void nextion(String command)
{
Serial.print(command); 
Serial.write(0xff); //We need to write the 3 ending bits to the Nextion as well
Serial.write(0xff); //it will tell the Nextion that this is the end of what we want to send.
Serial.write(0xff);
}

void setup() 
{
  pinMode(A0, INPUT);
  pinMode(14, INPUT);
  pinMode(12, INPUT);
  pinMode(5, INPUT);
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
}
nextion("g0.txt=\"WIFI CONNECTED\"");
Serial.write(0xff); 
Serial.write(0xff); 
Serial.write(0xff);
Serial.print("c0.val=1");
Serial.write(0xff); 
Serial.write(0xff); 
Serial.write(0xff);
}



void loop() 
{
    if((digitalRead(14) == 1)||(digitalRead(12) == 1))
    {
      nextion("detect.txt=\"NO ECG\"");
      ubidots.add("detect", 0);
    }
    else
    {
      nextion("detect.txt=\"ECG DETECTED\"");
      ubidots.add("detect", 1);
      Serial.print("add 1,0,"); // Changing the value of box n1
      Serial.print(analogRead(A0)/2);
      Serial.write(0xff); 
      Serial.write(0xff); 
      Serial.write(0xff);
      ubidots.add("ecg", analogRead(A0)/2);// Change for your variable name  
    }
    if (online==1)
    {
      bool bufferSent = false;
      bufferSent = ubidots.send();
    }

if (digitalRead(5) == 1) 
   {
      online = !online;
      Serial.print("c0.val=");
      Serial.print(online);
      Serial.write(0xff); 
      Serial.write(0xff); 
      Serial.write(0xff);
      delay(700);
    }
   }
