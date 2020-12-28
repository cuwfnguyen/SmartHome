import paho.mqtt.client as mqtt
import json
import serial
import time
s=serial.Serial('/dev/ttyUSB0',9600)

host = "node02.myqtthub.com"
port = 1883
interval = 600
topic1="IoT_BT1"
topic2="IoT_BT2"

def receive_arduino():
    value1=s.readline()
    value2=s.readline()
    value3=s.readline()
    value4=s.readline()
    
    valueG=value2[2:5]
    valueT=value3[2:4]
    valueH=value4[2:4]
    valueR=value1[2:3]
    mes=json.dumps({"gas":int(valueG.decode()), "temperature":int(valueT.decode()),"humidity":int(valueH.decode()),"rain":int(valueR.decode())});
    return mes
#def send_arduino():
    
def on_connect(client, userdata, flags, rc): 
    print("Connected with result code {0}".format(str(rc)))  
    client.subscribe(topic1)

def on_message(client, userdata, msg):
    #print("Message :" + msg.topic + " " + str(msg.payload))  
    if msg.topic=="IoT_BT1":
       # print(msg.payload)
        data=json.loads(msg.payload)
        if int(data["led1"]) == 1 :
            print("1on")
            s.write("led1ON".encode())
        if int(data["led1"]) == 0 :
            print("1off")
            s.write("led1OFF".encode())
        if int(data["led2"]) == 1 :
            print("2on")
            s.write("led2ON\n".encode())
        if int(data["led2"]) == 0 :
            print("2off")
            s.write("led2OFF\n".encode())
    
client = mqtt.Client("client01")
client.username_pw_set("client01","client01")
client.on_connect = on_connect  
client.on_message = on_message
client.connect(host,port,interval)
client.loop_start()
while True:
    client.publish(topic2,receive_arduino())
    #time.sleep(5)


    




