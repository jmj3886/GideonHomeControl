/*
 * Joshua Jarvis
 * 3/25/2017
 * 
 * This Arduino file listens for serial input of 1, 2, or 3
 * and upon read sends an RF signal to the corresponding switch 
 * to turn on/off an RF outlet.
 * 
 */
 
#define rfTransmitPin 4  //RF Transmitter pin = digital pin 4
#define ledPin 13        //Onboard LED = digital pin 13

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

void setup(){
  Serial.begin(9600);
  pinMode(rfTransmitPin, OUTPUT);    
  pinMode(ledPin, OUTPUT);
}

void loop(){
  if(Serial.available()){
    selection = Serial.readString();
  }
  
  if(selection=="1\n" && Switch1State == 0){
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
  digitalWrite(ledPin, HIGH);
  for(int i=0; i<dataSize; i=i+2){
      //Send HIGH signal
      digitalWrite(rfTransmitPin, HIGH);     
      delayMicroseconds(storedData[i]*timeDelay);
      //Send LOW signal
      digitalWrite(rfTransmitPin, LOW);     
      delayMicroseconds(storedData[i+1]*timeDelay);
  }
  digitalWrite(ledPin, LOW);
  delay(1000);
}

 
