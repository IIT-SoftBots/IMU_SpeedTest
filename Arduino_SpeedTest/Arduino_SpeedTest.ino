#include <SPI.h>

#define MOSI  11//COPI
#define MISO  12//CIPO
#define SCLK  13//sck
#define CS    10//cs

#define MPU9250_WhoAmI   0x75
#define LSM6DSRX_WhoAmI  0x0F

int t0, t1,t2;
int tempo,tempo2;
int16_t AccX =0;
byte dataToSend, xMSB, xLSB, yMSB, yLSB, zMSB, zLSB;

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
    writeRegister(0x1D, 0x00); //MPU9250
    //////////////////////////////////////////////////////LSM6DSRX
    // writeRegister(0x10, 0xA0); //LSM6DSRX
    //////////////////////////////////////////////////////////////
}

void loop() {    

  t0 = micros();
  
  dataToSend = 0x3B | 0b10000000;  //OUTX_AXEL + Readbit
  
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE3) ); //ArduinoUNO oscillator f.=16MHz. --> Max SPI speed = 16/2 = 8MHz, SPI_MODE3--> CPHA=CPOL=1
  
  digitalWrite(CS, LOW);   //CS Low to start trasmission
  
  SPI.transfer(dataToSend); 
  
  xMSB = SPI.transfer(0x00); 
  xLSB = SPI.transfer(0x00);
  
  yMSB = SPI.transfer(0x00);
  yLSB = SPI.transfer(0x00);
  
  zMSB = SPI.transfer(0x00);
  zLSB = SPI.transfer(0x00);
  
  digitalWrite(CS, HIGH); // take the chip select high to de-select:
  
  SPI.endTransaction();
  
  t1 = micros();
  
  int16_t AccX = (uint16_t)(xMSB<<8) | (uint16_t)xLSB;
  //Serial.print("AccX: ");
  //Serial.print(AccX);
  //Serial.write(AccX);   scambia dati senza stamparli --> effettivi 2000000Mbit*s
  // Serial.print("  ");
  
  int16_t AccY = (uint16_t)(yMSB<<8) | (uint16_t)yLSB;
  //Serial.print("AccY: ");
  //Serial.print(AccY);
  //Serial.print("  ");
  
  int16_t AccZ = (uint16_t)(zMSB<<8) | (uint16_t)zLSB;
  //Serial.print("AccZ: ");
  //Serial.println(AccZ);
  
  t2 = micros();
  
  tempo2 = t2 - t0;
  Serial.print("Tot Time:");
  Serial.print(tempo2);
  
  tempo = t1 - t0;
  Serial.print(" Read Time: ");
  Serial.println(tempo);
 
}


 uint64_t readRegister(byte thisRegister, int bytesToRead) {
  byte inByte = 0;           // incoming byte from the SPI
  uint64_t result = 0; 
  
  dataToSend = thisRegister | 0b10000000;
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3) );
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


void writeRegister(byte thisRegister, byte thisValue) {
  byte dataToSend = thisRegister;  // now combine the register address and the command into one byte:       
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
  digitalWrite(CS, LOW);// take the chip select low to select the device
  SPI.transfer(dataToSend); //Send register location
  SPI.transfer(thisValue); //Send register location
  digitalWrite(CS, HIGH);// take the chip select high to de-select:
  SPI.endTransaction();
}
