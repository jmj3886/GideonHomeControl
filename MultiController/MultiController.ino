 /* Joshua Jarvis
 * 3/25/2017
 * 
 * This Arduino file listens for serial input of 1, 2, or 3
 * and upon read sends an RF signal to the corresponding switch 
 * to turn on/off an RF outlet.
 * 
 */

#include <IRLibSendBase.h> 
#include <IRLib_P01_NEC.h>    
#include <IRLib_P02_Sony.h>   
#include <IRLibCombo.h>  
#include <IRLib_HashRaw.h>

 
#define rfTransmitPin 4  //RF Transmitter pin = digital pin 

//#1 On - 
const int on1Size = 160; 
byte on1[] = {95,15,15,4,15,5,4,15,16,4,4,15,5,15,5,15,15,4,5,15,4,15,5,15,4,15,5,15,15,4,16,93,5,15,15,4,15,5,4,15,15,5,4,15,5,15,4,16,15,4,5,15,4,15,5,15,4,15,5,15,15,4,16,93,4,16,15,4,15,5,4,15,15,5,4,15,5,15,4,15,16,4,4,16,4,15,5,15,4,15,5,15,15,4,15,94,4,15,16,4,15,5,4,15,15,5,4,15,5,15,4,15,15,5,4,16,4,15,4,16,4,15,5,15,15,4,15,94,4,15,16,4,15,5,4,15,15,5,4,15,5,15,4,15,15,5,4,15,5,15,4,16,4,15,4,16,15,4,13,255};
//#1 Off - 
const int off1Size = 122; 
byte off1[] = {94,15,15,5,15,4,5,15,15,5,4,15,4,16,4,15,5,15,15,4,5,15,4,15,5,15,4,15,16,4,15,94,4,15,15,5,15,4,5,15,15,4,5,15,4,16,4,15,4,16,15,4,5,15,4,15,5,15,4,15,15,5,15,93,5,15,15,5,15,4,5,15,15,4,5,15,4,15,5,15,4,15,16,4,4,16,4,15,4,16,4,15,15,5,15,93,5,15,15,4,16,4,4,16,15,4,5,15,4,15,5,15,4,15,15,5,4,15,5,15,4,255};
//#2 On - 
const int on2Size = 224; 
byte on2[] = {94,15,16,4,15,5,4,15,15,5,4,15,5,15,4,15,5,15,4,15,16,4,5,15,4,15,5,15,15,4,15,94,4,15,16,4,15,4,5,15,15,5,4,15,5,15,4,15,5,15,4,15,16,4,4,15,5,15,4,15,16,4,15,94,4,15,15,5,15,4,5,15,15,5,4,15,4,16,4,15,5,15,4,15,15,5,4,15,5,15,4,15,16,4,15,94,4,15,15,5,15,4,5,15,15,4,5,15,4,15,5,15,4,15,5,15,15,5,4,15,5,15,4,15,15,5,15,93,5,15,15,4,16,4,5,15,15,4,5,15,4,15,5,15,4,15,5,15,15,4,5,15,4,16,4,15,15,5,15,93,5,15,15,4,16,4,4,15,16,4,5,15,4,15,5,15,4,15,5,15,15,4,5,15,4,15,5,15,15,5,15,93,5,15,15,4,15,5,4,15,16,4,4,15,5,15,4,16,4,15,5,15,15,4,5,15,4,15,5,15,15,4,16,255};
//#2 Off -  
const int off2Size = 132; 
byte off2[] = {94,15,16,4,15,4,5,15,15,5,4,15,5,15,4,15,5,15,4,15,5,15,15,4,5,15,4,15,16,4,15,94,4,15,15,5,15,4,5,15,15,4,5,15,4,16,4,15,4,16,4,15,5,15,15,4,5,15,4,15,15,5,15,94,4,15,15,5,15,4,5,15,15,4,5,15,4,15,5,15,4,16,4,15,4,16,15,4,5,15,4,15,15,5,15,93,5,15,15,5,15,4,4,16,15,4,5,15,4,15,5,15,4,15,5,15,4,15,16,4,4,16,4,15,15,5,15,93,5,15,15,255};
//#3 On -  
const int on3Size = 132; 
byte on3[] = {95,14, 16,4, 15,4, 5,15, 15,5, 4,15, 5,15, 15,4, 5,15, 5,14, 5,15, 5,14, 5,15, 5,14, 16,4, 15,94, 4,15, 16,4, 15,4, 5,15, 15,4, 5,15, 5,15, 15,4, 5,15, 4,15, 5,15, 4,15, 5,15, 5,14, 16,4, 15,94, 4,15, 15,5, 15,4, 5,15, 15,4, 5,15, 5,15, 15,4, 5,15, 4,15, 5,15, 4,15, 5,15, 4,15, 16,4, 15,93, 5,15, 15,5, 15,4, 5,15, 15,4, 5,15, 4,15, 16,4, 5,15, 4,15, 5,15, 4,15, 5,15, 4,15, 16,4, 15,93, 5,15, 15,4};
//#3 Off -  
const int off3Size = 98; 
byte off3[] = {94,15,16,4,15,5,4,15,15,5,4,15,15,5,4,15,5,15,4,16,4,15,4,16,4,15,4,16,15,4,15,94,4,15,15,5,15,5,4,15,15,5,4,15,15,5,4,15,5,15,4,15,5,15,4,16,4,15,4,16,15,4,15,94,4,15,15,5,15,4,5,15,15,5,4,15,15,5,4,15,4,16,4,15,5,15,4,15,5,15,4,15,15,5,15,94,4,255};

//Variable to hold switch selection
String selection = "0"; 

//State of the switch off/on
int Switch1State = 0; 
int Switch2State = 0; 
int Switch3State = 0;

//Frequency - Used to slow down the signal transmission (can be from 75 - 135)
int timeDelay = 115;

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

void setup() {
  Serial.begin(9600);  
  pinMode(rfTransmitPin, OUTPUT);
  delay(2000); while (!Serial);
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
  }else if(selection=="1\n" && Switch1State == 0){
    Serial.println("#1 On");
    sendSignal(on1,on1Size);
  }else if(selection=="2\n" && Switch2State == 0){
    Serial.println("#2 On");
    sendSignal(on2,on2Size);
  }else if(selection=="3\n" && Switch3State == 0){
    Serial.println("#3 On");
    sendSignal(on3,on3Size);
  }else if(selection=="1\n" && Switch1State == 1){
    Serial.println("#1 Off");
    sendSignal(off1,off1Size);
  }else if(selection=="2\n" && Switch2State == 1){
    Serial.println("#2 Off");
    sendSignal(off2,off2Size);
  }else if(selection=="3\n" && Switch3State == 1){
    Serial.println("#3 Off");
    sendSignal(off3,off3Size);  
  }
  
 if(selection > "0"){
    switch(selection.toInt()){
      case 1:
        Switch1State = !Switch1State;
        break;
      case 2:
        Switch2State = !Switch2State;
        break;
      case 3:
        Switch3State = !Switch3State;
        break;
    } 
    selection = "0";
    delay(1000);
  }
}

/*------------------------------------------------------------------------------
   Send the stored signal to the FAN/LIGHT's RF receiver. A time delay is required to synchronise
   the digitalWrite timeframe with the 433MHz signal requirements. This has not been tested with different
   frequencies.
   ------------------------------------------------------------------------------ */
void sendSignal(byte *storedData, int dataSize){
  
  for(int i=0; i<dataSize; i=i+2){
      //Send HIGH signal
      digitalWrite(rfTransmitPin, HIGH);     
      delayMicroseconds(storedData[i]*timeDelay);
      //Send LOW signal
      digitalWrite(rfTransmitPin, LOW);     
      delayMicroseconds(storedData[i+1]*timeDelay);
  }
  delay(1000);
}

 
