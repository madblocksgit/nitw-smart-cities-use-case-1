from pyrsistent import inc
import serial
import paho.mqtt.client as mqtt

# create a client object to connect with broker
client=mqtt.Client()

# connect with broker
client.connect('broker.hivemq.com',1883)

# create an object
ser=serial.Serial('COM9',115200,timeout=0.5)

while True:
    if(ser.inWaiting()>0): # true
        incomingData=ser.readline()
        incomingData=incomingData.decode('utf-8')
        incomingData=incomingData.split(' ')
        hum=incomingData[1]
        temp=incomingData[-1][:-2]
        #print(hum,temp)
        pubData={}
        pubData['h']=hum
        pubData['t']=temp
        print(pubData)
        client.publish('iot/nit',str(pubData))
        print('Data Published')

