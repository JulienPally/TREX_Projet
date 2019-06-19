# coding: utf-8

import smbus
import time
import socket

bus=smbus.SMBus(1)
addr=0x07

reculer = [0x02,0x00,0xFF,0x00,0x00,0xFF,0x00,0x05,0xDC,0x05,0xDC,0x05,0xDC,0x05,0xDC,0x00,0x00,0x00,0x00,0x32,0x00,0x32,0x02,0x23,0x07,0x00]    #RECULER
avancer = [0x02,0xFF,0x01,0x00,0xFF,0x01,0x00,0x05,0xDC,0x05,0xDC,0x05,0xDC,0x05,0xDC,0x00,0x00,0x00,0x00,0x32,0x00,0x32,0x02,0x23,0x07,0x00]   #AVANCER
stop = [0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0xDC,0x05,0xDC,0x05,0xDC,0x05,0xDC,0x00,0x00,0x00,0x00,0x32,0x00,0x32,0x02,0x23,0x07,0x00]   #STOP
gauche = [0x02,0x00,0xFF,0x00,0x00,0x00,0x00,0x05,0xDC,0x05,0xDC,0x05,0xDC,0x05,0xDC,0x00,0x00,0x00,0x00,0x32,0x00,0x32,0x02,0x23,0x07,0x00]   #GAUCHE
droite = [0x02,0x00,0x00,0x00,0x00,0xFF,0x00,0x05,0xDC,0x05,0xDC,0x05,0xDC,0x05,0xDC,0x00,0x00,0x00,0x00,0x32,0x00,0x32,0x02,0x23,0x07,0x00]   #DROITE

socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket.bind(('', 54000))
socket.listen(5)
client, address = socket.accept()
print ("{} connected".format( address ))

while (1==1):

    try:
        
        reponse = client.recv(1)
        if (reponse != ""):
                cmd = reponse.decode("utf-8")

                if(cmd == '1'):
                    """socket.send(u"message bien recu.")"""
                    bus.write_i2c_block_data(addr,0x0F,avancer) #AVANCER
                    time.sleep(0.1)
                    message_recua = bus.read_byte(addr)
                    time.sleep(0.1)
                    print ("avancer")

                elif(cmd == '2'):
                    """socket.send(u"message bien recu.")"""
                    bus.write_i2c_block_data(addr,0x0F,reculer) #RECULER
                    time.sleep(0.1)
                    message_recur = bus.read_byte(addr)
                    time.sleep(0.1)
                    print ("reculer")

                elif(cmd == '3'):
                    """socket.send(u"message bien recu.")"""
                    bus.write_i2c_block_data(addr,0x0F,gauche) #GAUCHE
                    time.sleep(0.1)
                    message_recug = bus.read_byte(addr)
                    time.sleep(0.1)
                    print ("gauche")

                elif(cmd == '4'):
                    """socket.send(u"message bien recu.")"""
                    bus.write_i2c_block_data(addr,0x0F,droite) #DROITE
                    time.sleep(0.1)
                    message_recud = bus.read_byte(addr)
                    time.sleep(0.1)
                    print ("droite")

                elif(cmd == '0'):
                    """socket.send(u"message bien recu.")"""
                    bus.write_i2c_block_data(addr,0x0F,stop) #STOP
                    time.sleep(0.1)
                    message_recus = bus.read_byte(addr)
                    time.sleep(0.1)
                    print ("arret")
                
        else:
            bus.write_i2c_block_data(addr,0x0F,stop) #STOP
            time.sleep(0.1)
            message_recus2 = bus.read_byte(addr)
            time.sleep(0.1)
            print ("Arret")

    except OSError as e:
        print(e)
        client.close()
        #socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        #socket.bind(('', 54000))
        socket.listen(5)
        client, address = socket.accept()
        print ("{} connected".format( address ))

client.close()
stock.close()
