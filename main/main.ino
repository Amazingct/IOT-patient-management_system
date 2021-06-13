String command;

void setup() 
{
  pinMode(A0, INPUT);
  Serial.begin(9600);


}

void loop() 
{
Serial.print("add 1,0,"); // Changing the value of box n1
Serial.print(analogRead(A0));
Serial.write(0xff); //We need to write the 3 ending bits to the Nextion as well
Serial.write(0xff); //it will tell the Nextion that this is the end of what we want to send.
Serial.write(0xff);


}
