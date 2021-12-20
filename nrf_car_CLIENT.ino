// nrf24_reliable_datagram_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, reliable messaging client
// with the RHReliableDatagram class, using the RH_NRF24 driver to control a NRF24 radio.
// It is designed to work with the other example nrf24_reliable_datagram_server
// Tested on Uno with Sparkfun WRL-00691 NRF24L01 module
// Tested on Teensy with Sparkfun WRL-00691 NRF24L01 module
// Tested on Anarduino Mini (http://www.anarduino.com/mini/) with RFM73 module
// Tested on Arduino Mega with Sparkfun WRL-00691 NRF25L01 module

#include <RHReliableDatagram.h>
#include <RH_NRF24.h>
#include <SPI.h>

#define joyVert  A0
#define  joyHorz A1

int JPV = 512;
int JPH = 512;

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2


RH_NRF24 driver;
  

RHReliableDatagram RadioManager(driver, CLIENT_ADDRESS);

uint8_t MC[3];
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];

void setup() 
{
  
  if (!RadioManager.init())

    MC[2] = 0;
}

    
void loop()
{
  JPV = analogRead(joyVert);
  JPH = analogRead(joyHorz);

    if(JPV < 460){
    MC[2] = 1;
  MC[0] = map(joyVert, 460, 0, 0, 255);
  MC[1] = map(joyVert, 460, 0, 0, 255);
    }
    
    else if(JPV > 564){
      MC[2] = 0;
  MC[0] = map(joyVert, 564, 1023, 0, 255);
  MC[1] = map(joyVert, 564, 1023, 0, 255);
    }
    else{
        MC[0] = 0;
          MC[1] = 0;
            MC[2] = 0;
    }
    if(JPH < 460){
      JPH = map(JPH, 460, 0, 0, 255);

      MC[0] = MC[0] - JPH;
      MC[1] = MC[1] + JPH;
      
      if(MC[0] < 0)MC[0] =0;
      if(MC[1] > 255)MC[1] =255;
    }

 else if (JPH > 564){
  JPH = map(JPH, 564, 1023, 0, 255);

      MC[0] = MC[0] + JPH;
      MC[1] = MC[1] - JPH;

        if(MC[0] > 255)MC[0] = 255;
      if(MC[1] < 0)MC[1] = 0;
  }

  if (MC[0] < 8)MC[0] = 0;
  if (MC[1] < 8)MC[1] = 0;
  

  
  if (RadioManager.sendtoWait(MC, sizeof(MC), SERVER_ADDRESS))
  {
    
    uint8_t len = sizeof(buf);
    uint8_t from;   
    
  }}
