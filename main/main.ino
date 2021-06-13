#include "Ubidots.h"

/****************************************
* Define Instances and Constants
****************************************/   
 
const char* UBIDOTS_TOKEN = "BBFF-YRpT6QwkDeCAjElEUd9NBLD0VqZAKb";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "falconP";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "falcon123";      // Put here your Wi-Fi password 

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
  Serial.begin(9600);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);

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
//// send the value of analog input 0:
nextion("detect.txt=\"ECG DETECTED\"");
ubidots.add("detect", 1);
Serial.print("add 1,0,"); // Changing the value of box n1
Serial.print(analogRead(A0));
Serial.write(0xff); //We need to write the 3 ending bits to the Nextion as well
Serial.write(0xff); //it will tell the Nextion that this is the end of what we want to send.
Serial.write(0xff);
ubidots.add("ECG", analogRead(A0));// Change for your variable name  
}

  bool bufferSent = false;
  bufferSent = ubidots.send(); // Will send data to a device label that matches the device Id
  if (bufferSent) 
  {
  
  }
}
