#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>

Enrf24 radio(P2_0, P2_1, P2_2);
const uint8_t rxaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };

const char *str_on = "ON";
const char *str_off = "OFF";
const char *str_F = "F";
const char *str_B = "B";
const char *str_L = "L";
const char *str_R = "R";
const char *str_E = "E";
const char *str_O = "O";

void dump_radio_status_to_serialport(uint8_t);

void setup() {
  
  //LED specific outputs
  //P1DIR |= ( BIT0 | BIT1 | BIT2 | BIT3 | BIT4 );
  //P2DIR |= ( BIT3 | BIT4 );
  
  //PORT 2 OUTPUTS - general
  //P2DIR |= ( BIT5 | BIT6 | BIT7 );
  
  //ENABLE XIN XOUT
  //P2SEL &= ~(BIT6|BIT7);
  //P2OUT = 0;
 
  Serial.begin(9600);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  
  radio.begin();  // Defaults 1Mbps, channel 0, max TX power
  dump_radio_status_to_serialport(radio.radioState());

  radio.setRXaddress((void*)rxaddr);
  
  //P1DIR |= ( BIT0 | BIT1 | BIT2 | BIT3 | BIT4 );
  pinMode(P1_0, OUTPUT);
    digitalWrite(P1_0, LOW);  
    
  pinMode(P1_1, OUTPUT);
    digitalWrite(P1_1, LOW);
    
  pinMode(P1_2, OUTPUT);
    digitalWrite(P1_2, LOW);
    
   pinMode(P1_3, OUTPUT);
    digitalWrite(P1_3, LOW);
    
  pinMode(P1_4, OUTPUT);
    digitalWrite(P1_4, LOW);
    
  pinMode(P2_3, OUTPUT);
    digitalWrite(P2_3, LOW);
    
  pinMode(P2_4, OUTPUT);
    digitalWrite(P2_4, LOW);
    
  pinMode(P2_5, OUTPUT);
    digitalWrite(P2_5, LOW);
    
  pinMode(P2_6, OUTPUT);
   digitalWrite(P2_6, LOW);
    
  pinMode(P2_7, OUTPUT);
    digitalWrite(P2_7, LOW);
    
  
  
  radio.enableRX();  // Start listening
}

void loop() {
  char inbuf[33];
  
  dump_radio_status_to_serialport(radio.radioState());  // Should show Receive Mode
  
  
  
  while (!radio.available(true))
    ;
  if (radio.read(inbuf)) {
    Serial.print("Received packet: ");
    Serial.println(inbuf);

    if (!strcmp(inbuf, str_F)){
         motor_OFF();
        letter_F();
        motor_F();
        }
        
   
    if (!strcmp(inbuf, str_B)){
       motor_OFF();
        letter_B();
        motor_B();
        }
        
        
    if (!strcmp(inbuf, str_L)){
       motor_OFF();
        letter_L();
        motor_L();
        }
        
   
    if (!strcmp(inbuf, str_R)){
       motor_OFF();
        letter_R();
        motor_R();
        }
        
    
    if (!strcmp(inbuf, str_E)){
       motor_OFF();
        letter_E();
        motor_OFF();
        }
        
    
    if (!strcmp(inbuf, str_O)){
        letter_OFF();
        motor_OFF();
        }
  }
  //else letter_F();
}

/*
PIN MAP FOR LED:
1.0 = led enable
1.1 = a
1.2 = c
1.3 = d
1.4 = e
2.3 = f
2.4 = g
section b = ground
*/
void letter_F(){ // a, e, f, g
    digitalWrite(P1_0, HIGH); //enable
    digitalWrite(P1_1, HIGH); //a
    digitalWrite(P1_2, LOW);  //c
    digitalWrite(P1_3, LOW);  //d
    digitalWrite(P1_4, HIGH); //e
    digitalWrite(P2_3, HIGH); //f
    digitalWrite(P2_4, HIGH); //g
}
void letter_B() { // c, d, e, f, g
    digitalWrite(P1_0, HIGH); //enable
    digitalWrite(P1_1, LOW); //a
    digitalWrite(P1_2, HIGH); //c
    digitalWrite(P1_3, HIGH); //d
    digitalWrite(P1_4, HIGH); //e
    digitalWrite(P2_3, HIGH); //f
    digitalWrite(P2_4, HIGH); //g
}
void letter_L(){ // d, e, f
    digitalWrite(P1_0, HIGH); //enable
    digitalWrite(P1_1, LOW); //a
    digitalWrite(P1_2, LOW); //c
    digitalWrite(P1_3, HIGH); //d
    digitalWrite(P1_4, HIGH); //e
    digitalWrite(P2_3, HIGH); //f
    digitalWrite(P2_4, LOW); //g
}
void letter_R(){ // e, g
    digitalWrite(P1_0, HIGH); //enable
    digitalWrite(P1_1, LOW); //a
    digitalWrite(P1_2, LOW); //c
    digitalWrite(P1_3, LOW); //d
    digitalWrite(P1_4, HIGH); //e
    digitalWrite(P2_3, LOW); //f
    digitalWrite(P2_4, HIGH); //g
}
void letter_E(){ // a, d, e, f, g
    digitalWrite(P1_0, HIGH); //enable
    digitalWrite(P1_1, HIGH); //a
    digitalWrite(P1_2, LOW); //c
    digitalWrite(P1_3, HIGH); //d
    digitalWrite(P1_4, HIGH); //e
    digitalWrite(P2_3, HIGH); //f
    digitalWrite(P2_4, HIGH); //g
}

void letter_OFF(){
    digitalWrite(P1_0, LOW); //enable
    digitalWrite(P1_1, LOW); //a
    digitalWrite(P1_2, LOW); //c
    digitalWrite(P1_3, LOW); //d
    digitalWrite(P1_4, LOW); //e
    digitalWrite(P2_3, LOW); //f
    digitalWrite(P2_4, LOW); //g
}

void motor_F(){
digitalWrite(P2_5, HIGH); //enable
  
   digitalWrite(P2_6, LOW); //xin
   digitalWrite(P2_7, LOW); //xout

}

void motor_B(){
digitalWrite(P2_5, HIGH); //enable
    digitalWrite(P2_6, HIGH); //xin
    digitalWrite(P2_7, LOW); //xout
  
}

void motor_L(){
    
    
        digitalWrite(P2_5, HIGH); //enable
    digitalWrite(P2_6, LOW); //xin
    digitalWrite(P2_7, HIGH); //xout //rifgr

}

void motor_R(){
    
   
         digitalWrite(P2_5,HIGH); //enable
     digitalWrite(P2_6, HIGH); //xin
    digitalWrite(P2_7, HIGH); //xout*/right
}

void motor_OFF(){
    digitalWrite(P2_5, LOW); //enable
    //digitalWrite(P2_6, LOW); //xin
    //digitalWrite(P2_7, LOW); //xout
                         P2OUT &= ~BIT6;
                     P2OUT &= ~BIT7;
}

void pause(){
  motor_OFF();
  delay(1000);
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
