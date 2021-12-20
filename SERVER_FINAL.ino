// nrf24_reliable_datagram_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, reliable messaging server
// with the RHReliableDatagram class, using the RH_NRF24 driver to control a NRF24 radio.
// It is designed to work with the other example nrf24_reliable_datagram_client
// Tested on Uno with Sparkfun WRL-00691 NRF24L01 module
// Tested on Teensy with Sparkfun WRL-00691 NRF24L01 module
// Tested on Anarduino Mini (http://www.anarduino.com/mini/) with RFM73 module
// Tested on Arduino Mega with Sparkfun WRL-00691 NRF25L01 module

#include <RHReliableDatagram.h>
#include <RH_NRF24.h>
#include <SPI.h>

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2



RH_NRF24 Radiodriver;

RHReliableDatagram RadioManager(Radiodriver, SERVER_ADDRESS);
uint8_t ReturnMessage[] = "JoyStick Data Received";
int V=500;
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
int enA = 9;
int in1 = 3;
int in2 = 4;

int enB = 5;
int in3 = 7;
int in4 = 6;

void setup() {
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT); 
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
  Serial.begin(9600);
  if (!RadioManager.init())
    Serial.println("init failed");}


void loop()
{
  if (RadioManager.available())
  {
    // Wait for a message addressed to us from the client
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (RadioManager.recvfromAck(buf, &len, &from))
    {
     

      if(buf[2] == 1 && buf[0]>240 && buf[1]>240){
        digitalWrite(in1, LOW);
         digitalWrite(in2, HIGH);
          digitalWrite(in3, LOW);
           digitalWrite(in4, HIGH);   
           digitalWrite(enA,HIGH);
           digitalWrite(enB,HIGH);      
      }
      else if(buf[2] == 0 && buf[0]>200 && buf[1]>200){
        digitalWrite(in1, HIGH);
         digitalWrite(in2, LOW);
          digitalWrite(in3, HIGH);
           digitalWrite(in4, LOW); 
            digitalWrite(enA,HIGH);
           digitalWrite(enB,HIGH); 
      }
      else if(buf[0]>240 && buf[1]<10 && buf[2] == 0){

                  digitalWrite(in1, HIGH);
         digitalWrite(in2, LOW);
          digitalWrite(in3, LOW);
           digitalWrite(in4, HIGH);
          digitalWrite(enA,HIGH);
           digitalWrite(enB,HIGH); 
      }
      else if(buf[1]>240 && buf[0]<10 && buf[2] == 0){
        
        digitalWrite(in1, LOW);
         digitalWrite(in2, HIGH);
          digitalWrite(in3, HIGH);
           digitalWrite(in4, LOW); 
           digitalWrite(enA,HIGH);
           digitalWrite(enB,HIGH);
      }
      else{
        digitalWrite(enA,LOW);
           digitalWrite(enB,LOW); 
      }

    }
  }
}

 //analogWrite(enA, buf[0]);
   //     analogWrite(enB, buf[1]);
        
    //Serial.print("buf[0] = ");
    //Serial.println(buf[0]);
    //Serial.print("buf[1] = ");
    //Serial.println(buf[1]);
    //Serial.print("buf[2] = ");
   //Serial.println(buf[2]);
       
