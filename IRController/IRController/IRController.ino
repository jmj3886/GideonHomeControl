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
    mySender.send(UNKNOWN,0xF6D1C6CE,48);
  }else if(selection=="H2\n"){
    Serial.println("Temp Up");
    mySender.send(UNKNOWN,0x39D41DC6,10);
  }else if(selection=="H3\n"){
    Serial.println("Temp Down");
    mySender.send(UNKNOWN,0xF6D1C6CE,48);
  }else if(selection=="H4\n"){
    Serial.println("Rotate");
    mySender.send(UNKNOWN,0xF6D1C6CE,48);
  }
  
  selection = "0";
}

