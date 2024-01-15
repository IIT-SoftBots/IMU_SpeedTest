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
#include <project.h>
int IMU_ack;

//uint8 SensorHub[6] = {LSM6DSRX_SENSOR_HUB_1, LSM6DSRX_SENSOR_HUB_2, LSM6DSRX_SENSOR_HUB_3, LSM6DSRX_SENSOR_HUB_4, LSM6DSRX_SENSOR_HUB_5, LSM6DSRX_SENSOR_HUB_6};
struct st_imu_data g_imu, g_imuNew;
uint8 Mag[2][10][6];
uint8 Accel[2][10][6];
uint8 Gyro[2][10][6];
uint8 Temp[2];
uint8 GDA;
uint8 XLDA;
uint8 SENS_HUB_ENDOP;
uint16 t0;
uint16 t1;
uint16 tempo[10];
uint8 j;
uint8 count;
uint8 k;
uint8 var;

int main()
{   MY_TIMER_Start();                 
    PACER_TIMER_Start();    
    SPI_IMU_Start();
	SPI_IMU_Init();
	SPI_IMU_Enable();
	SPI_IMU_ClearRxBuffer();
	SPI_IMU_ClearTxBuffer();
	SPI_IMU_ClearFIFO();							
    CyDelay(10);
  
    CyGlobalIntEnable;
    
    uint8 i;
    uint8 who;
    UART_Start();
    Control_Reg_1_Write(2);
    for (k=0;k<2; k++){
    Control_Reg_1_Write(k+1);
   	WriteControlRegisterSPI(MPU9250_PWR_MGMT_1, 0x10); 
	CyDelay(10);	
	WriteControlRegisterSPI(MPU9250_USER_CTRL, 0x20);  //I2C master enable - disable I2C (prima 0x30)
	CyDelay(10);
    WriteControlRegisterSPI(MPU9250_CONFIG, 0x06); //Gyro & Temp Low Pass Filter 0x01 = 184Hz, 0x02 = 92Hz, 0x04 = 20Hz, 0x05 = 10Hz
    CyDelay(10);	
    WriteControlRegisterSPI(MPU9250_ACCEL_CONFIG, 0x00); // Acc full scale select 0x00 = 2g 0x08 = 4g 0x10 = 8g 0x18 = 16g
    CyDelay(10);
    WriteControlRegisterSPI(MPU9250_ACCEL_CONFIG2, 0x05);
    CyDelay(10);
    
   // WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00);
 /*   CyDelay(100);
    OneShot_ReadRoutine(EXT_SENS_ADDR,LIS2MDL_WHO_AM_I); //LIS2MDL -->valore WHO_AM_I = 64
    OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_A,0x00); //
    CyDelay(1);
    OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_A,0x00); //
    OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_B,0x02);
    OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_C,0x10);
    Continuous_ReadRoutine(EXT_SENS_ADDR,LIS2MDL_OUTX_L_REG,0x06);
    */
  }
    
   // Control_Reg_1_Write(3);
    j = 0;
    count =0;
    
    for(;;)
    {   t0 = (uint16)MY_TIMER_ReadCounter();
for (k=0;k<1; k++){
   // Control_Reg_1_Write(k+1);
//      ------------------------------------------------------------------------READ MAG
     /*   do 
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
        CyDelayUs(100);  
        ReadControlRegisterSPI(LSM6DSRX_WHO_AM_I); 
           
        for (i = 0; i < 6; i++){
            Mag[k][j][i]= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_1 + i);  
        }
       
        WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00);   
        CyDelayUs(100);
         
      */
          
        
             Accel[k][j][0] = ReadControlRegisterSPI(MPU9250_ACCEL_XOUT_L );
             Accel[k][j][1] = ReadControlRegisterSPI(MPU9250_ACCEL_XOUT_H );
             Accel[k][j][2] = ReadControlRegisterSPI(MPU9250_ACCEL_YOUT_L );
             Accel[k][j][3] = ReadControlRegisterSPI(MPU9250_ACCEL_YOUT_H );
             Accel[k][j][4] = ReadControlRegisterSPI(MPU9250_ACCEL_ZOUT_L );
             Accel[k][j][5] = ReadControlRegisterSPI(MPU9250_ACCEL_ZOUT_H );
            
        /*
        for (i = 0; i < 6; i++){
            Gyro[k][j][i] = ReadControlRegisterSPI(LSM6DSRX_OUTX_L_G + i);
        }*/
}
      // Control_Reg_1_Write(3);

//}        

     
//      ---------------------------------------------------------------------READ AXELS

        //CyDelay(1);
        t1 = (uint16) MY_TIMER_ReadCounter();
        tempo[j] = (uint16)(t0-t1);
    
        j = j + 1;
        
        if (j > 9) {
            
            for(count = 0; count < 10; count++){ 
                for (k=0;k<1;k++){
                UART_PutChar(count);
                UART_PutChar(0);
            
                var = (uint8)(tempo[count] & 0xFF);
                UART_PutChar(var);
                var = (uint8) (tempo[count] >> 8);
                UART_PutChar(var);
                
                
                for (i = 0; i < 6; i++){
                    UART_PutChar( Accel[k][count][i]);
                }
              /*  
                for (i = 0 ; i < 6; i++){
                    UART_PutChar( Gyro[k][count][i]);
                }
                                    
                for (i = 0; i < 6; i++){
                    UART_PutChar( Mag[k][count][i]);
                }
                */
                UART_PutChar('c');
                UART_PutChar('i');
                UART_PutChar('a');
}
            }
            
            j = 0;
            
        } 
        
        MY_TIMER_REG_Write(1);
        
        MY_TIMER_REG_Write(0);
        
        
    }
    
return 0;
    
}
/* [] END OF FILE */
