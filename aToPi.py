import paho.mqtt.client as mqtt
import json
import serial
s=serial.Serial('/dev/ttyUSB0',9600)

def receive_arduino():
    valueLed=1
    value1=s.readline()
    value2=s.readline()
    value3=s.readline()
    
    valueG=value1[2:5]
    valueT=value2[2:4]
    valueH=value3[2:4]
    mes=json.dumps({"led":valueLed,"gas":valueG.decode(), "temperature":valueT.decode(),"humidity":valueH.decode()});
    print(str(mes))
    #data=json.loads(mes.payload)
   # print(str(data["led"]))
  #  if(s.readline())
    #day khong phai in ra ma la get du lieu de gui sang app

#def send_arduino():
    #ham nay de gui du lieu sang arduino xu ly
    
while(1):
    receive_arduino()

