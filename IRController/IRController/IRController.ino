/* send.ino Example sketch for IRLib2
 *  Illustrates how to send a code.
 */
#include <IRLibSendBase.h>    // First include the send base
//Now include only the protocols you wish to actually use.
//The lowest numbered protocol should be first but remainder 
//can be any order.
#include <IRLib_P01_NEC.h>    
#include <IRLib_P02_Sony.h>   
#include <IRLibCombo.h>     // After all protocols, include this
// All of the above automatically creates a universal sending
// class called "IRsend" containing only the protocols you want.
// Now declare an instance of that sender.
#include <IRLib_HashRaw.h>    //Only use raw sender

#define POWER_DATA_LEN 100
uint16_t powerData[POWER_DATA_LEN]={
  1270, 450, 1258, 438, 410, 1258, 1286, 434, 
  1258, 438, 410, 1258, 434, 1262, 430, 1262, 
  434, 1262, 434, 1262, 430, 1262, 1282, 7190, 
  1282, 438, 1258, 434, 398, 1274, 1286, 434, 
  1258, 410, 422, 1274, 434, 1262, 430, 1262, 
  434, 1262, 430, 1266, 430, 1262, 1282, 7186, 
  1274, 450, 1258, 414, 430, 1262, 1282, 438, 
  1258, 434, 410, 1262, 430, 1266, 430, 1262, 
  430, 1266, 430, 1266, 430, 1262, 1282, 7186, 
  1282, 442, 1258, 434, 410, 1262, 1282, 414, 
  1282, 434, 410, 1262, 430, 1266, 430, 1262, 
  430, 1266, 430, 1262, 434, 1262, 1282, 7186, 
  1274, 426, 1270, 1000};

#define UP_DATA_LEN 24
uint16_t upData[UP_DATA_LEN]={
  1198, 502, 1234, 458, 390, 1306, 1194, 502, 
  1238, 454, 390, 1302, 378, 1318, 1238, 458, 
  390, 1302, 378, 1318, 394, 1298, 378, 1000};

#define DOWN_DATA_LEN 24
uint16_t downData[DOWN_DATA_LEN]={
  1202, 498, 1286, 410, 438, 1254, 1282, 414, 
  1254, 442, 422, 1270, 1206, 490, 390, 1302, 
  394, 1302, 358, 1338, 358, 1334, 362, 1000};

#define ROTATE_DATA_LEN 24
uint16_t rotateData[ROTATE_DATA_LEN]={
  1198, 498, 1238, 458, 390, 1302, 1198, 498, 
  1238, 458, 390, 1302, 374, 1318, 358, 1338, 
  1198, 498, 390, 1302, 378, 1318, 374, 1000};

IRsendRaw myRawSender;
IRsend mySender;
String selection = "0"; 

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
}

void loop() {
  if(Serial.available()){
    selection = Serial.readString();
  }
  
  if(selection=="T1\n"){
    Serial.println("Power");
    mySender.send(NEC,0x5FAFA05,0);
  }else if(selection=="T2\n"){
    Serial.println("Mute");
    mySender.send(NEC,0x5FA38C7,0);
  }else if(selection=="T3\n"){
    Serial.println("Volume Up");
    mySender.send(NEC,0x5FA02FD,0);
  }else if(selection=="T4\n"){
    Serial.println("Volume Down");
    mySender.send(NEC,0x5FABA45,0);
  }else if(selection=="T5\n"){
    Serial.println("Input");
    mySender.send(NEC,0x5FA58A7,0);
  }else if(selection=="T6\n"){
    Serial.println("Up");
    mySender.send(NEC,0x5FA9A65,0);
  }else if(selection=="T7\n"){
    Serial.println("Down");
    mySender.send(NEC,0x5FA8A75,0);
  }else if(selection=="H1\n"){
    Serial.println("Power");
    myRawSender.send(powerData,POWER_DATA_LEN,36);
  }else if(selection=="H2\n"){
    Serial.println("Temp Up");
    myRawSender.send(upData,UP_DATA_LEN,36);
  }else if(selection=="H3\n"){
    Serial.println("Temp Down");
    myRawSender.send(downData,DOWN_DATA_LEN,36);
  }else if(selection=="H4\n"){
    Serial.println("Rotate");
    myRawSender.send(rotateData,ROTATE_DATA_LEN,36);
  }
  
  selection = "0";
}

