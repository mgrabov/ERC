#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>

Enrf24 radio(P2_0, P2_1, P2_2);  // P2.0=CE, P2.1=CSN, P2.2=IRQ
const uint8_t txaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };

const char *str_on = "ON";
const char *str_off = "OFF";
const char *str_F = "F";
const char *str_B = "B";
const char *str_L = "L";
const char *str_R = "R";
const char *str_E = "E";
const char *str_O = "O";

//set pin numbers
const int buttonPin = P1_1;     
const int buttonPin2 = P1_2;     
const int buttonPin3 = P1_3;     
const int buttonPin4 = P1_4;    

int buttonState=0;        
int buttonState2=0;            
int buttonState3=0;             
int buttonState4=0;   

void dump_radio_status_to_serialport(uint8_t);

void setup() {
  Serial.begin(9600);

  //pinMode(buttonPin, INPUT_PULLUP);
  //pinMode(buttonPin2, INPUT_PULLUP);
  //pinMode(buttonPin3, INPUT_PULLUP);
  //pinMode(buttonPin4, INPUT_PULLUP);
  
   pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);


  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  radio.begin();  // Defaults 1Mbps, channel 0, max TX power
  dump_radio_status_to_serialport(radio.radioState());

  radio.setTXaddress((void*)txaddr);
}

void loop() {
   buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2); 
  buttonState3 = digitalRead(buttonPin3); 
  buttonState4 = digitalRead(buttonPin4);  
  
  if (buttonState==LOW)
{
  Serial.print("Sending packet: ");
  Serial.println(str_F);
  radio.print(str_F);
  radio.flush();  // Force transmit (don't wait for any more data)
  dump_radio_status_to_serialport(radio.radioState());  // Should report IDLE
  delay(100);}
if (buttonState2==LOW)
{
  Serial.print("Sending packet: ");
  Serial.println(str_B);
  radio.print(str_B);
  radio.flush();  
  dump_radio_status_to_serialport(radio.radioState());  // Should report IDLE
  delay(100);}
  if (buttonState3==LOW)
{
  Serial.print("Sending packet: ");
  Serial.println(str_L);
  radio.print(str_L);
  radio.flush();  // Force transmit (don't wait for any more data)
  dump_radio_status_to_serialport(radio.radioState());  // Should report IDLE
  delay(100);
}
if (buttonState4==LOW)
{
  Serial.print("Sending packet: ");
  Serial.println(str_R);
  radio.print(str_R);
  radio.flush();  //
  dump_radio_status_to_serialport(radio.radioState());  // Should report IDLE
  delay(100);
}
  else 
 { 
  Serial.print("Sending packet: ");
  Serial.println(str_E);
  radio.print(str_E);
  radio.flush();  // Force transmit (don't wait for any more data)
  dump_radio_status_to_serialport(radio.radioState());  // Should report IDLE
 // delay(1000);
 }
  //Serial.print("Sending packet: ");
 // Serial.println(str_O);
 // radio.print(str_O);
 // radio.flush();  //
 // dump_radio_status_to_serialport(radio.radioState());  // Should report IDLE
 // delay(1000);
}

void dump_radio_status_to_serialport(uint8_t status)
{
  Serial.print("Enrf24 radio transceiver status: ");
  switch (status) {
    case ENRF24_STATE_NOTPRESENT:
      Serial.println("NO TRANSCEIVER PRESENT");
      break;

    case ENRF24_STATE_DEEPSLEEP:
      Serial.println("DEEP SLEEP <1uA power consumption");
      break;

    case ENRF24_STATE_IDLE:
      Serial.println("IDLE module powered up w/ oscillators running");
      break;

    case ENRF24_STATE_PTX:
      Serial.println("Actively Transmitting");
      break;

    case ENRF24_STATE_PRX:
      Serial.println("Receive Mode");
      break;

    default:
      Serial.println("UNKNOWN STATUS CODE");
  }
}
