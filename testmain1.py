import paho.mqtt.client as mqtt
import json
import serial
s=serial.Serial('/dev/ttyUSB0',9600)

host = "mqtt.eclipse.org"
port = 1883
interval = 600
topic1="IoT_BT1"
topic2="IoT_BT2"

def receive_arduino():
    value1=s.readline()
    value2=s.readline()
    value3=s.readline()
    
    valueG=value1[2:5]
    valueT=value2[2:4]
    valueH=value3[2:4]
    mes=json.dumps({"gas":int(valueG.decode()), "temperature":int(valueT.decode()),"humidity":int(valueH.decode())});
    return mes
#def send_arduino():
    
def on_connect(client, userdata, flags, rc): 
    print("Connected with result code {0}".format(str(rc)))  
    client.subscribe(topic1)
    client.publish(topic2,receive_arduino())

def on_message(client, userdata, msg):  
    #print("Message :" + msg.topic + " " + str(msg.payload))  
    if msg.topic=="IoT_BT1":
       # print(msg.payload)
        data=json.loads(msg.payload)
        if int(data["led1"]) == 1 :
            #print("1")
            s.write("led1ON\n".encode())
        if int(data["led1"]) == 0 :
            s.write("led1OFF\n".encode())
          #  print("0")
   # if msg.topic=="IoT_BT2":
    #    led2=msg.payload
    #    s.write(led2)
    #    print(led2)   
    #data=json.loads(msg.payload)
    #print("h: "+str(data["led"]))
    
client = mqtt.Client("digi_mqtt_test")
client.on_connect = on_connect  
client.on_message = on_message
client.connect(host,port,interval)
client.loop_forever()


    




