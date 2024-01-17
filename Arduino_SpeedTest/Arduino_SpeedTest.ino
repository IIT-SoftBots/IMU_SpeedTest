#include <SPI.h>

#define MOSI 11//COPI
#define MISO  12//CIPO
#define SCLK  13//sck
#define CS 10//cs

#define MPU9250_WhoAmI   0x75
#define LSM6DSRX_WhoAmI  0x0F
  int t0, t1;
 int tempo;
   int16_t AccX =0;
byte dataToSend;
void setup() {
    Serial.begin(9600);
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
unsigned int AccX = readRegister(0x3F,2); 
    t1 = micros(); 
 /* 
  byte lsb = readRegister(0x40,1);  //Read the temperature data 
  byte msb = readRegister(0x3F,1);  //Read the temperature data 

   int16_t AccX = (msb << 8) | lsb;
 

  char Ping = readRegister(0x2A ,1);  //Read the temperature data 
  char Ping = readRegister(0x2B ,1);  //Read the temperature data 

  char Ping = readRegister(0x2C ,1);  //Read the temperature data 
  char Ping = readRegister(0x2D ,1);  //Read the temperature data 
*/

  Serial.println(AccX);
  
  tempo = t1 - t0;
  Serial.print(" tempo = ");
  Serial.print(tempo);
  Serial.print("\n");
}


unsigned int readRegister(byte thisRegister, int bytesToRead) {
  byte inByte = 0;           // incoming byte from the SPI

  unsigned int result = 0; 
dataToSend = thisRegister | 0b10000000;

  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3) );
  
  digitalWrite(CS, LOW);  
  
  SPI.transfer(dataToSend); 
  
  result = SPI.transfer(0x00);
  
 
  bytesToRead--;// decrement the number of bytes left to read:
  if (bytesToRead > 0) {// if you still have another byte to read:
    result = result << 8; // shift the first byte left, then get the second byte:
    inByte = SPI.transfer(0x00);
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

  digitalWrite(CS, LOW);// take the chip select low to select the device:
  
  SPI.transfer(dataToSend); //Send register location
  SPI.transfer(thisValue); //Send register location
  
  digitalWrite(CS, HIGH);// take the chip select high to de-select:
  
  SPI.endTransaction();
}
