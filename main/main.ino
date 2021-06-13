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

}

void loop() 
{


if((digitalRead(14) == 1)||(digitalRead(12) == 1))
{
nextion("detect.txt=\"NO ECG\"");
}
else{
//// send the value of analog input 0:
nextion("detect.txt=\"ECG DETECTED\"");
Serial.print("add 1,0,"); // Changing the value of box n1
Serial.print(analogRead(A0)/2);
Serial.write(0xff); //We need to write the 3 ending bits to the Nextion as well
Serial.write(0xff); //it will tell the Nextion that this is the end of what we want to send.
Serial.write(0xff);
}

}
