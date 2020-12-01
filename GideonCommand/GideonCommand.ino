/* Joshua Jarvis
 * 12/1/2020
 * 
 * This Arduino file listens for a serial input command,
 * interprets the command into either RF or IR, then 
 * executes the command with the message sent
 * with the command. 
 * 
 */

#include <IRLibAll.h>
#include <IRLibSendBase.h> 
#include <IRLib_P01_NEC.h>    
#include <IRLib_P02_Sony.h>   
#include <IRLibCombo.h>  
#include <IRLib_HashRaw.h>
#include <RCSwitch.h>


//RF TRANSITION/RECEIVING INFORMATION
//IR TRANSMITTER PIN = DIGITAL PIN 5
//IR RECEIVER PIN = DIGITAL PIN 2
RCSwitch RF_SENDER_RECEIVER = RCSwitch();  


//IR TRANSMITION/RECEIVING INFORMATION
IRsendRaw RAW_IR_SENDER;  //IR TRANSMITTER PIN = DIGITAL PIN 3
IRsend IR_SENDER;  //IR TRANSMITTER PIN = DIGITAL PIN 3
IRrecvPCI IR_RECEIVER(4);  //IR RECEIVER PIN = DIGITAL PIN 4
IRdecode IR_DECODER;


void setup() {
    Serial.begin(9600);  
    pinMode(RF_TRANSMITION_PIN, OUTPUT);
    delay(2000); while (!Serial);
}


void loop() {
    String command = "";
    String protocol = "";
    uint16_t messageLength = 0;
    Sting messageType = "";
    
    if(Serial.available()){
        //COMMAND MESSAGE = "<COMMAND> <PROTOCOL> <MESSAGE_LENGTH> <MESSAGE> <OPTIONAL_IR_MESSAGE_TYPE>"
        command = Serial.readString();
        while(!Serial.available()){}
        protocol = Serial.readString();
        if(command == "SEND")
        {
            while(!Serial.available()){}
            messageLength = toInt(Serial.readString());
            byte message[messageLength];
            while(!Serial.available()){}
            for(int i = 0; i < messageLength; i++)
            {
                messageLength[i] = (byte) strtol(Serial.readString().c_str());
            }
        }
    }
  
    if(command == "SEND")
    {
        if(protocol == "IR")
        {
            int messageTypeInt = NEC;
            while(!Serial.available()){}
            messageType = Serial.readString();
            if(messageType == "NEC")
            {
                messageTypeInt = NEC;
            }
            IR_SENDER.send(messageTypeInt, message[0], 0);
        }
        else if(protocol == "RIR")
        {
            RAW_IR_SENDER.send(message, messageLength, 36);
        }
        else if(protocol == "RF")
        {
            RF_SENDER_RECEIVER.enableTransmit(5);
            RF_SENDER_RECEIVER.send(message[0], message[1]);
            RF_SENDER_RECEIVER.disableTransmit();
        }
    }
    else if(command == "REC")
    {
        if(protocol == "IR")
        {
            IR_RECEIVER.enableIRIn();            
            while(!IR_RECEIVER.getResults()){}
            IR_DECODER.decode();
            IR_DECODER.dumpResults(true);
            IR_RECEIVER.disableIRIn();
        }
        else if(protocol == "RF")
        {
            RF_SENDER_RECEIVER.enableReceive(0);  
            if (!RF_SENDER_RECEIVER.available()){}           
            int value = RF_SENDER_RECEIVER.getReceivedValue();            
            if (value == 0)
            {
                Serial.print("Unknown encoding");
            } 
            else 
            {     
                Serial.print("Received ");       
                Serial.print( RF_SENDER_RECEIVER.getReceivedValue() );      
                Serial.print(" / ");     
                Serial.print( RF_SENDER_RECEIVER.getReceivedBitlength() );      
                Serial.print("bit ");      
                Serial.print("Protocol: ");     
                Serial.println( RF_SENDER_RECEIVER.getReceivedProtocol() );    
            }
            RF_SENDER_RECEIVER.resetAvailable();
            RF_SENDER_RECEIVER.disableReceive();
        }        
    }
    delay(500);
}
