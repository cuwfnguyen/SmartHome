#include "DHT.h"
  const int gas =A0;
  const int buzzer=2;
  const int irsensor=3;
  const int light=6;
  const int irlight=4;
  const int dht1=5;
  DHT dht(dht1, DHT11);
  String serialData="";
  boolean onSerialRead = false;
  
void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(gas,INPUT);
  pinMode(irsensor,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(irlight,OUTPUT);
  pinMode(light,OUTPUT);
  serialData.reserve(200);
}

void procesSerialData() 
{
    Serial.print("Data " + serialData);
    if (serialData == "led1ON") 
    {    
        digitalWrite(light, HIGH);
    } 
    else if(serialData=="led1OFF")
    {
        digitalWrite(light, LOW);
    }
//    else if (serialData == "led2ON") 
//    {    
//        digitalWrite(light, HIGH);
//    } 
//    else if(serialData=="led2OFF")
//    {
//        digitalWrite(light, LOW);
//    }
    serialData = "";
    onSerialRead = false;
}
void loop() 
{
  float h = dht.readHumidity();    
  float t = dht.readTemperature();
  if(digitalRead(irsensor)==0)
  {
   digitalWrite(irlight,HIGH);
   delay(3000);
  }
  else if(digitalRead(irsensor)==1)
  {
    digitalWrite(irlight,LOW);
  }
  
  if(analogRead(gas)>=400)
  {
    digitalWrite(buzzer,HIGH);
  }
  else if(analogRead(gas)<400)
  {
    digitalWrite(buzzer,LOW);
  }
  Serial.print("G:");
  Serial.println(analogRead(gas));
  Serial.print("T:");
  Serial.println(t);
  Serial.print("H:");
  Serial.println(h);
   if (onSerialRead) 
   {
        procesSerialData();
    }
}
void serialEvent() 
{
    while (Serial.available()) 
    {
        char inChar = (char)Serial.read();
        if (inChar == '\n') 
        {
            onSerialRead = true;
        } else {
            serialData += inChar;
        }
    }
}
