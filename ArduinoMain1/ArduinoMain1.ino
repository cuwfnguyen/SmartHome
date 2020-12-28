#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
  const int gas =A0;
  const int buzzer=2;
  const int irsensor=3;
  const int light=6;
  const int fan=7;
  const int irlight=4;
  const int dht1=5;
  const int rain=8;
  const int switch1=9;
  const int switch2=10;
  const int lightsensor=A1;
  const int lslight=A2;
  LiquidCrystal_I2C lcd(0x27,16,2);
  DHT dht(dht1, DHT11);
  String serialData="";
  boolean onSerialRead = false;
  
  byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};
void setup() {
  Serial.begin(9600);
  lcd.init();  
  lcd.backlight();
  lcd.print("Nhiet do: ");
  lcd.setCursor(0,1);
  lcd.print("Do am: ");
  lcd.createChar(1, degree);
  dht.begin();  
  
  pinMode(gas,INPUT);
  pinMode(irsensor,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(irlight,OUTPUT);
  pinMode(light,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(rain, INPUT);
  pinMode(lightsensor,INPUT);
  pinMode(lslight,OUTPUT);
  
  serialData.reserve(200);
}

void procesSerialData() 
{
    Serial.print("Data " + serialData);
    if (serialData == "led1ONled2OFF") 
    {  
       digitalWrite(light, HIGH);
       digitalWrite(fan, LOW);
    } 
    else if(serialData == "led1OFFled2OFF")
    {
       digitalWrite(light, LOW);
       digitalWrite(fan, LOW);
    }
    
    if (serialData == "led1ONled2ON") 
    {    
       digitalWrite(fan, HIGH);
       digitalWrite(light, HIGH);
    } 
    else if(serialData=="led1OFFled2ON")
    {
       digitalWrite(light, LOW);
       digitalWrite(fan, HIGH);
    }
    serialData = "";
    onSerialRead = false;
}
//Dieu chinh den bang nut nhan
void led()
{ 
   if(digitalRead(switch2)==0)
   {
    digitalWrite(light, LOW);
   }
   if(digitalRead(switch2)==1)
   {
    digitalWrite(light, HIGH);
   }
   if(digitalRead(switch1)==0)
   {
    digitalWrite(fan, LOW);
   }
   if(digitalRead(switch1)==1)
   {
    digitalWrite(fan, HIGH);
   }
   
  }
  
void loop() 
{
  if(digitalRead(lightsensor)==1)
  {
    digitalWrite(lslight,HIGH);
   }
  else if(digitalRead(lightsensor)==0)
  {
    digitalWrite(lslight,LOW);
   }
   
  float h = dht.readHumidity();    
  float t = dht.readTemperature();
  //LCD
  if (isnan(t) || isnan(h)) {
  } 
  else {
    lcd.setCursor(10,0);
    lcd.print(round(t));
    lcd.print(" ");
    lcd.write(1);
    lcd.print("C");

    lcd.setCursor(10,1);
    lcd.print(round(h));
    lcd.print(" %");    
  }
  //Den cau thang
  if(digitalRead(irsensor)==0)
  {
   digitalWrite(irlight,HIGH);
   delay(3000);
  }
  else if(digitalRead(irsensor)==1)
  {
    digitalWrite(irlight,LOW);
  }
  
  //Gas
  if(analogRead(gas)>=400)
  {
    digitalWrite(buzzer,HIGH);
  }
  else if(analogRead(gas)<400)
  {
    digitalWrite(buzzer,LOW);
  }
  float rain1=digitalRead(rain);
  Serial.print("R:");
  Serial.println(rain1);
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
//   else if(!onSerialRead)
//   {
//      led();
//   }
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
