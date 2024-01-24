#include <SPI.h>

#define MOSI  11//COPI
#define MISO  12//CIPO
#define SCLK  13//sck
#define CS    10//cs

#define MPU9250_WhoAmI   0x75
#define LSM6DSRX_WhoAmI  0x0F

uint16_t t0, t1,t2;
uint16_t tempo,tempo2;
int16_t AccX =0;
byte dataToSend, xMSB, xLSB, yMSB, yLSB, zMSB, zLSB,DATA_RDY;

void setup() {
    Serial.begin(2000000);
    pinMode(MOSI, OUTPUT);
    pinMode(MISO, INPUT);
    pinMode(SCLK,OUTPUT);
    pinMode(CS,OUTPUT); 
    digitalWrite(CS,HIGH); //disable device
    SPI.begin();
    //////////////////////////////////////////////////////MPU9250
    writeRegister(0x1A, 0x06); //MPU9250
    writeRegister(0x1C, 0x00); //MPU9250
    writeRegister(0x1D, 0x08); //MPU9250 nolpf
    writeRegister(0x6C, 0b00000111);
    //writeRegister(0x1D, 0x02); //MPU9250  lpf 218hz, odr=1khz

    //////////////////////////////////////////////////////LSM6DSRX
    // writeRegister(0x10, 0xA0); //LSM6DSRX
    //////////////////////////////////////////////////////////////
      dataToSend = 0x3B | 0b10000000;  //OUTX_AXEL + Readbit
      t0= micros();
}
  

void loop() {    

  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE3) ); //ArduinoUNO oscillator f.=16MHz. --> Max SPI speed = 16/2 = 8MHz, SPI_MODE3--> CPHA=CPOL=1

  do{
      digitalWrite(CS, LOW);   //CS Low to start trasmission
      
   SPI.transfer(0x3A | 0b10000000);
     delayMicroseconds(5);

   DATA_RDY = SPI.transfer(0x00);
   DATA_RDY = DATA_RDY & 0b00000001;
digitalWrite(CS, HIGH);   //CS Low to start trasmission
}
  while(DATA_RDY == 0);
    digitalWrite(CS, LOW);
  t2 = micros();
  tempo= t2-t0;
  //t1 = micros();
  SPI.transfer(dataToSend); 
    delayMicroseconds(5);

  xMSB = SPI.transfer(0x00);
    delayMicroseconds(5);
 
  Serial.write(xMSB);
    delayMicroseconds(5);
  xLSB = SPI.transfer(0x00);
    delayMicroseconds(5);

  Serial.write(xLSB);
  delayMicroseconds(5);

  
  yMSB = SPI.transfer(0x00);
    delayMicroseconds(5);

   Serial.write(yMSB);
     delayMicroseconds(5);

  yLSB = SPI.transfer(0x00);
  delayMicroseconds(5);

    Serial.write(yLSB);
        delayMicroseconds(5);

  //delayMicroseconds(5);
  zMSB = SPI.transfer(0x00);
    delayMicroseconds(5);

   Serial.write(zMSB);
     delayMicroseconds(5);

  zLSB = SPI.transfer(0x00);
    delayMicroseconds(5);

    Serial.write(zLSB);
      delayMicroseconds(5);
  digitalWrite(CS, HIGH);
SPI.endTransaction();
  
    
 // take the chip select high to de-select:

  //int16_t AccX = (uint16_t)(xMSB<<8) | (uint16_t)xLSB;
  //Serial.print("AccX: ");
  //Serial.print(AccX);
  //Serial.write(AccX);  // scambia dati senza stamparli --> effettivi 2000000Mbit*s
   //Serial.print("  ");
  
 // int16_t AccY = (uint16_t)(yMSB<<8) | (uint16_t)yLSB;
 // Serial.print("AccY: ");
  //Serial.write(AccY);
  //Serial.print("  ");
  
//  int16_t AccZ = (uint16_t)(zMSB<<8) | (uint16_t)zLSB;
  //Serial.print("AccZ: ");
  //Serial.write(AccZ);
  //  Serial.print("  ");
  byte lTempo = (byte)(tempo & 0x00FF);
  byte mTempo = (byte)((tempo & 0xFF00)>> 8);
  Serial.write(mTempo);
    delayMicroseconds(5);

  Serial.write(lTempo);
  delayMicroseconds(5);

  //Serial.println(lTempo);
  

  Serial.write('A');
    delayMicroseconds(5);

  Serial.write('B');
    delayMicroseconds(5);

  Serial.write('C');
    delayMicroseconds(5);

  Serial.write('D');
    delayMicroseconds(5);


  //Serial.println(tempo2);
  
  //Serial.print(" Read Time: ");
 // Serial.println(tempo);
 

}

/*
 uint64_t readRegister(byte thisRegister, int bytesToRead) {
  byte inByte = 0;           // incoming byte from the SPI
  uint64_t result = 0; 
  
  dataToSend = thisRegister | 0b10000000;
  SPI.beginTransaction(SPISettings(800000, MSBFIRST, SPI_MODE3) );
  digitalWrite(CS, LOW);  
  SPI.transfer(dataToSend); 
  result = SPI.transfer(0x00);
  bytesToRead--;// decrement the number of bytes left to read:
  if (bytesToRead > 0) {// if you still have another byte to read:
    result = result << 8; // shift the first byte left, then get the second byte:
    inByte = SPI.transfer(0x00);
    inByte = (uint64_t)inByte;
    result = result | inByte; // combine the byte you just got with the previous one:
    bytesToRead--; // decrement the number of bytes left to read:
  }
  digitalWrite(CS, HIGH); // take the chip select high to de-select:
  SPI.endTransaction();
  return (result);
}
*/

void writeRegister(byte thisRegister, byte thisValue) {     
  SPI.beginTransaction(SPISettings(800000, MSBFIRST, SPI_MODE3));
  digitalWrite(CS, LOW);// take the chip select low to select the device
  SPI.transfer(thisRegister); //Send register location
  SPI.transfer(thisValue); //Send register location
  digitalWrite(CS, HIGH);// take the chip select high to de-select:
  SPI.endTransaction();
}
