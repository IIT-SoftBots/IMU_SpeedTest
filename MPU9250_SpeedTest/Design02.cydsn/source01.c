/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "header01.h"
#include "globals.h"
/********************************** *********************************************
* Function Name: Write Control Register
*********************************************************************************/

void WriteControlRegisterSPI(uint8 address, uint8 dta){
	
	SPI_IMU_ClearRxBuffer();
	SPI_IMU_ClearTxBuffer();
	SPI_IMU_ClearFIFO();
	SPI_IMU_WriteByte(LSM6DSRX_WCR | address);
	while(!( SPI_IMU_ReadStatus() & SPI_IMU_STS_TX_FIFO_EMPTY));		
	SPI_IMU_WriteByte(dta);
	while(!( SPI_IMU_ReadStatus() & SPI_IMU_STS_TX_FIFO_EMPTY));
}

/*******************************************************************************
* Function Name: Read Control Register
*********************************************************************************/
uint8 ReadControlRegisterSPI(uint8 address){
	uint8 controlreg = 0;
	SPI_IMU_WriteByte(LSM6DSRX_RCR | address);
    while(!( SPI_IMU_ReadStatus() & SPI_IMU_STS_TX_FIFO_EMPTY));
    SPI_IMU_WriteByte(0x00);
	while(!( SPI_IMU_ReadStatus() & SPI_IMU_STS_SPI_DONE));
	controlreg = SPI_IMU_ReadByte();        //real data
	return controlreg;
}


void InitIMU() {
    InitAxelGyro();
    //InitMag();
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS,0b01000000); //Enable I2C master mode with external sensor
    //CyDelay(10);//Enable I2C master mode with external sensor
}



void OneShot_ReadRoutine1(uint8 address, uint8 subaddress,uint8 slave_config){
    uint8 XLDA;
    uint8 SENS_HUB_ENDOP;
    uint8 Data;
    uint8 i;
    uint16 t1;
    uint16 t0;
    uint16 tempo;
    uint8 tempoLSB, tempoMSB;
    

        
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x40);  //18ms
    CyDelayUs(100);
    WriteControlRegisterSPI(LSM6DSRX_SLV0_ADD, address | 0x01); //28ms
    CyDelayUs(10);
    WriteControlRegisterSPI(LSM6DSRX_SLV0_SUBADD, subaddress); //10
    CyDelayUs(10);
           
    WriteControlRegisterSPI(LSM6DSRX_SLV0_CONFIG, 0b00000110); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled //17
     CyDelayUs(10);
    WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x4C); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled  //10
    CyDelayUs(10);  
                
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00);   //17
    CyDelayUs(100); 
    
    i = ReadControlRegisterSPI(LSM6DSRX_WHO_AM_I);
    
    i = ReadControlRegisterSPI(LSM6DSRX_OUTX_L_A);
        UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTX_H_A);
        UART_PutChar(i);
   i= ReadControlRegisterSPI(LSM6DSRX_OUTY_L_A); //21
UART_PutChar(i);
  i = ReadControlRegisterSPI(LSM6DSRX_OUTY_H_A);
        UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTZ_L_A);
        UART_PutChar(i);
   i= ReadControlRegisterSPI(LSM6DSRX_OUTZ_H_A); //21
UART_PutChar(i);
    CyDelayUs(10);
    
        
    i = ReadControlRegisterSPI(LSM6DSRX_OUTX_L_G);
        UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTX_H_G);
        UART_PutChar(i);

            i = ReadControlRegisterSPI(LSM6DSRX_OUTY_L_G);
        UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTY_H_G);
        UART_PutChar(i);
        
            i = ReadControlRegisterSPI(LSM6DSRX_OUTZ_L_G);
        UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTZ_H_G);
        UART_PutChar(i);
        
    
    do 
    {
        XLDA = ReadControlRegisterSPI(LSM6DSRX_STATUS_REG);  //20
                
    }
    while ((XLDA & 0b00000001) == 0); 
    
     
    do 
    {
        SENS_HUB_ENDOP = ReadControlRegisterSPI(LSM6DSRX_STATUS_MASTER_MAINPAGE);   
       // UART_PutChar(SENS_HUB_ENDOP);
    }
    while ((SENS_HUB_ENDOP & 0b00000001) == 0);
   // UART_PutChar(SENS_HUB_ENDOP);
  
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x40);   
    CyDelayUs(100);  
    
    WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x08);
    
    CyDelayUs(300);  
      
    ReadControlRegisterSPI(LSM6DSRX_WHO_AM_I);  
     

   
        i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_1);  
        CyDelayUs(10);
        UART_PutChar(i);
                i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_2);  
                CyDelayUs(10);
        UART_PutChar(i);
               i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_3);  
            CyDelayUs(10);
        UART_PutChar(i);
                i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_4);  
                CyDelayUs(10);
        UART_PutChar(i);
                i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_5);  
                CyDelayUs(10);
        UART_PutChar(i);
                i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_6); 
                CyDelayUs(10);
        UART_PutChar(i);
        
     
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00); 

    CyDelayUs(100);  
        
    
    
}

uint8 OneShot_ReadRoutine(uint8 address, uint8 subaddress){
    uint8 XLDA;
    uint8 SENS_HUB_ENDOP;
    uint8 Data;
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x40); 
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_SLV0_ADD, address | 0x01); 
    CyDelay(1);   
    WriteControlRegisterSPI(LSM6DSRX_SLV0_SUBADD, subaddress); 
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_SLV0_CONFIG, 0x01); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x4C); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00); 
    ReadControlRegisterSPI(LSM6DSRX_OUTX_H_A); 
    
    do 
    {
        XLDA = ReadControlRegisterSPI(LSM6DSRX_STATUS_REG);  
        
    }
    while ((XLDA & 0b00000001) == 0); 
    
    
    do 
    {
        SENS_HUB_ENDOP = ReadControlRegisterSPI(LSM6DSRX_STATUS_MASTER_MAINPAGE);
        
    }
    while ((SENS_HUB_ENDOP & 0b00000001) == 0);

    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x40); 
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x08); 
    CyDelay(1);
    CyDelayUs(300);  
    
    ReadControlRegisterSPI(LSM6DSRX_WHO_AM_I);  
    
    Data = ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_1);  
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00); 
   // UART_PutChar(Data);
    return Data;
}

void Continuous_ReadRoutine(uint8 address, uint8 subaddress, uint8 slave_config){
 
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x40);
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_SLV0_ADD, address | 0x01);  
    CyDelay(1);  
    WriteControlRegisterSPI(LSM6DSRX_SLV0_SUBADD, subaddress); 
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_SLV0_CONFIG, slave_config); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x4C); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00); 
    CyDelay(1);
 }

/*
void Read( uint8 slave_config){
    uint8 XLDA;
    uint8 SENS_HUB_ENDOP;
    uint8 i;
    ReadControlRegisterSPI(LSM6DSRX_WHO_AM_I); 
    do 
    {
        XLDA = ReadControlRegisterSPI(LSM6DSRX_STATUS_REG);        
    }
    while ((XLDA & 0b00000001) == 0);

    do 
    {
        SENS_HUB_ENDOP = ReadControlRegisterSPI(LSM6DSRX_STATUS_MASTER_MAINPAGE);
    }
    while ((SENS_HUB_ENDOP & 0b00000001) == 0);

    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x40); 
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x08); 
    CyDelay(1);
    CyDelayUs(300);   
    for (i=0; i < slave_config; i++)
    {
        Mag[i]= ReadControlRegisterSPI(SensorHub[i]);    
    }
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00); 
}
*/

void OneShot_WriteRoutine (uint8 address, uint8 subaddress, uint8 data){
    uint8 WR_ONCE_DONE;
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x40);
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_SLV0_ADD, address | 0x00);
    CyDelay(1);    
    WriteControlRegisterSPI(LSM6DSRX_SLV0_SUBADD, subaddress); 
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_SLV0_CONFIG, 0x00); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled
    CyDelay(1);
     
    WriteControlRegisterSPI(LSM6DSRX_DATAWRITE_SLV0, data); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x4C); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled
    CyDelay(1);
        do 
    {
        WR_ONCE_DONE = ReadControlRegisterSPI(LSM6DSRX_STATUS_MASTER);
    }
    while ((WR_ONCE_DONE & 0b10000000) == 0);
    
    WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x08); 
    CyDelayUs(300);   
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00); 
    
}


/*******************************************************************************
* Function Name: Read Acc's Data of IMU n
*********************************************************************************/
void ReadAcc()
{   /*uint8 low=0, high=0;
   
    low=ReadControlRegisterSPI(LSM6DSRX_OUTX_L_A);
    high=ReadControlRegisterSPI(LSM6DSRX_OUTX_H_A);
	Accel[0] = high; 
	Accel[1] = low; 
	low=0;
    high=0;
			
	//read Y
    low=ReadControlRegisterSPI(LSM6DSRX_OUTY_L_A);
    high=ReadControlRegisterSPI(LSM6DSRX_OUTY_H_A);
	Accel[2] = high; 
	Accel[3] = low; 
	low=0;
    high=0;
	 	
	//read Z
    low=ReadControlRegisterSPI(LSM6DSRX_OUTZ_L_A);
    high=ReadControlRegisterSPI(LSM6DSRX_OUTZ_H_A);
	Accel[4] = high; 
	Accel[5] = low;
	low=0;
    high=0;*/
}


/*******************************************************************************
* Function Name: Read Gyro's Data of IMU n
*********************************************************************************/
void ReadGyro()
{   /*uint8 low=0, high=0;
    low=ReadControlRegisterSPI(LSM6DSRX_OUTX_L_G);
    high=ReadControlRegisterSPI(LSM6DSRX_OUTX_H_G);
	Gyro[0] = high; 
	Gyro[1] = low; 
	low=0, high=0;
			
	//read Y
    low=ReadControlRegisterSPI(LSM6DSRX_OUTY_L_G);
    high=ReadControlRegisterSPI(LSM6DSRX_OUTY_H_G);
	Gyro[2] = high; 
	Gyro[3] = low; 
	low=0, high=0;
		
	//read Z
    low=ReadControlRegisterSPI(LSM6DSRX_OUTZ_L_G);
    high=ReadControlRegisterSPI(LSM6DSRX_OUTZ_H_G);
	Gyro[4] = high; 
	Gyro[5] = low;
	low=0, high=0;*/
}

/*******************************************************************************
* Function Name: Read Temperature Data of IMU n
*********************************************************************************/
void ReadTemp()
{
	uint8 low=0, high=0;	
    low=ReadControlRegisterSPI(LSM6DSRX_OUT_TEMP_L);
    high=ReadControlRegisterSPI(LSM6DSRX_OUT_TEMP_H);

	Temp[0] = high; 
	Temp[1] = low; 
	low=0, high=0;
}

/*******************************************************************************
* Function Name: IMU Read
*********************************************************************************/	
void ReadIMU(){/*
    uint16 tmp = 0, j = 0;
   // uint8 c = 1;
    int16 aux_int16;
    // Packet: header + imu id(uint8) + imu flags(uint8) + crc
    uint8 accX1;
    uint8 accX2;
    uint8 accY1;
    uint8 accY2;
    uint8 accZ1;
    uint8 accZ2;
    
    ChipSelectorIMU(0);
    ReadAcc();
   // ReadGyro();
   // ReadTemp();
    
    for (j = 0; j < 3; j++) {
        tmp = Accel[2*j];
        g_imuNew.accel_value[j] = (int16)(tmp<<8 | Accel[2*j + 1]);
    }

    /*
    for (j = 0; j < 3; j++) {
        tmp = Gyro[2*j];
        g_imuNew.gyro_value[j] = (int16)(tmp<<8 | Gyro[2*j + 1]);
    }      
    
    tmp = Temp[0];
    g_imuNew.temp_value = (int16)(tmp<<8 | Temp[1]);
    
    
    aux_int16 = (int16) g_imuNew.accel_value[0];      
    accX1 = ((char*)(&aux_int16))[0];
    UART_PutChar(accX1); //MSB
    
    accX2 = ((char*)(&aux_int16))[1];
    UART_PutChar(accX2);   //LSB
    
    accX1=0;
    accX2=0;
           
    aux_int16 = (int16) g_imuNew.accel_value[1];
    accY1 = ((char*)(&aux_int16))[0]; 
    UART_PutChar(accY1);
    
    accY2 = ((char*)(&aux_int16))[1];
    UART_PutChar(accY2);
     
    accY1=0;
    accY2=0;       
 
    aux_int16 = (int16) g_imuNew.accel_value[2];
    accZ1 = ((char*)(&aux_int16))[0];
    UART_PutChar(accZ1);
    
    accZ2 = ((char*)(&aux_int16))[1];
    UART_PutChar(accZ2);
    

    accZ1=0;
    accZ2=0;
    /*
 index = 0;
while(!(UART_ReadTxStatus() & UART_TX_STS_COMPLETE) && index++ <= 1000){}
  
       aux_int16 = (int16) g_imu.gyro_value[0];
            single_packet[c + 1] = ((char*)(&aux_int16))[0];
            single_packet[c] = ((char*)(&aux_int16))[1];

            aux_int16 = (int16) g_imu.gyro_value[1];
            single_packet[c + 3] = ((char*)(&aux_int16))[0];
            single_packet[c + 2] = ((char*)(&aux_int16))[1];

            aux_int16 = (int16) g_imu.gyro_value[2];
            single_packet[c + 5] = ((char*)(&aux_int16))[0];
            single_packet[c + 4] = ((char*)(&aux_int16))[1];

            c = c + 6;

            aux_int16 = (int16) g_imu.temp_value;
            single_packet[c + 1] = ((char*)(&aux_int16))[0];
            single_packet[c] = ((char*)(&aux_int16))[1];
            
            for(k=0; k < packet_length; k++) {
            packet_data[k] = (uint8) single_packet[k]; 
        }
            c = 1;
            */
        
     
}

/* [] END OF FILE */
