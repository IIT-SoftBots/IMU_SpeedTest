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

#include <project.h>
#include <stdlib.h>
#include <stdio.h>




//LSM6DSRX Register definition

#define EXT_SENS_ADDR 0b00111100
#define LSM6DSRX_WCR                    0x00
#define LSM6DSRX_RCR                    0x80

#define LSM6DSRX_INT1_CTRL              0x0D
#define LSM6DSRX_INT2_CTRL              0x0E
#define LSM6DSRX_WHO_AM_I               0x0F
#define LSM6DSRX_CTRL1_XL               0x10
#define LSM6DSRX_CTRL2_G                0x11      
#define LSM6DSRX_CTRL3_C                0x12
#define LSM6DSRX_CTRL4_C                0x13
#define LSM6DSRX_CTRL5_C                0x14
#define LSM6DSRX_CTRL6_C                0x15
#define LSM6DSRX_CTRL7_G                0x16
#define LSM6DSRX_CTRL8_XL               0x17
#define LSM6DSRX_CTRL9_XL               0x18
#define LSM6DSRX_CTRL10_C               0x19


#define LSM6DSRX_STATUS_REG             0x1E
#define LSM6DSRX_OUT_TEMP_L             0x20
#define LSM6DSRX_OUT_TEMP_H             0x21
#define LSM6DSRX_OUTX_L_G               0x22
#define LSM6DSRX_OUTX_H_G               0x23
#define LSM6DSRX_OUTY_L_G               0x24
#define LSM6DSRX_OUTY_H_G               0x25
#define LSM6DSRX_OUTZ_L_G               0x26
#define LSM6DSRX_OUTZ_H_G               0x27
#define LSM6DSRX_OUTX_L_A               0x28
#define LSM6DSRX_OUTX_H_A               0x29
#define LSM6DSRX_OUTY_L_A               0x2A
#define LSM6DSRX_OUTY_H_A               0x2B
#define LSM6DSRX_OUTZ_L_A               0x2C
#define LSM6DSRX_OUTZ_H_A               0x2D
#define LSM6DSRX_STATUS_MASTER_MAINPAGE 0x39
#define LSM6DSRX_TIMESTAMP0             0x40
#define LSM6DSRX_TIMESTAMP1             0x41
#define LSM6DSRX_TIMESTAMP2             0x42
#define LSM6DSRX_TIMESTAMP3             0x43

#define LSM6DSRX_MD1_CFG                0x5E
#define LSM6DSRX_MD2_CFG                0x5F

#define LSM6DSRX_INTERNAL_FREQ_FINE     0x63

#define LSM6DSRX_X_OFS_USR              0x73
#define LSM6DSRX_Y_OFS_USR              0x74
#define LSM6DSRX_Z_OFS_USR              0x75

#define LSM6DSRX_FUNC_CFG_ACCESS        0x01
#define LSM6DSRX_SENSOR_HUB_1           0x02
#define LSM6DSRX_SENSOR_HUB_2           0x03
#define LSM6DSRX_SENSOR_HUB_3           0x04
#define LSM6DSRX_SENSOR_HUB_4           0x05
#define LSM6DSRX_SENSOR_HUB_5           0x06
#define LSM6DSRX_SENSOR_HUB_6           0x07
#define LSM6DSRX_MASTER_CONFIG          0x14
#define LSM6DSRX_SLV0_ADD               0x15
#define LSM6DSRX_SLV0_SUBADD            0x16
#define LSM6DSRX_SLV0_CONFIG            0x17
#define LSM6DSRX_DATAWRITE_SLV0         0x21
#define LSM6DSRX_STATUS_MASTER          0x22



//LIS2MDL Register definition
#define LIS2MDL_WCR                    0x00
#define LIS2MDL_RCR                    0x80

#define LIS2MDL_WHO_AM_I               0x4F
#define LIS2MDL_CFG_REG_A              0x60
#define LIS2MDL_CFG_REG_B              0x61
#define LIS2MDL_CFG_REG_C              0x62
#define LIS2MDL_INT_CRTL_REG           0x63
#define LIS2MDL_INT_SOURCE_REG         0x64
#define LIS2MDL_INT_THS_L_REG          0x65
#define LIS2MDL_INT_THS_H_REG          0x66
#define LIS2MDL_STATUS_REG             0x67
#define LIS2MDL_OUTX_L_REG             0x68
#define LIS2MDL_OUTX_H_REG             0x69
#define LIS2MDL_OUTY_L_REG             0x6A
#define LIS2MDL_OUTY_H_REG             0x6B
#define LIS2MDL_OUTZ_L_REG             0x6C
#define LIS2MDL_OUTZ_H_REG             0x6D
#define LIS2MDL_TEMP_OUT_L_REG         0x6E
#define LIS2MDL_TEMP_OUT_H_REG         0x6F

extern uint8 SensorHub[6];
void OneShot_ReadRoutine1(uint8 address, uint8 subaddress,uint8 slave_config);
void Read(uint8 slave_config);
void Continuous_ReadRoutine(uint8 address, uint8 subaddress, uint8 slave_config);
uint8 OneShot_ReadRoutine (uint8 address, uint8 subaddress);
void OneShot_WriteRoutine (uint8 address, uint8 subaddress, uint8 data);
void ReadIMU();
void InitIMU();
void InitAxelGyro();
void InitMag();
void ReadAcc(); //reads acc of IMU n
void ReadGyro();//reads gyro of IMU n
void ReadTemp();//reads temperature of IMU n
uint8 ReadControlRegisterSPI(uint8 address);
void WriteControlRegisterSPI(uint8 address, uint8 dta);

uint8 ReadControlRegisterI2C(uint8 address);
void WriteControlRegisterI2C(uint8 address, uint8 dta);
void ChipSelectorIMU(int n);
/* [] END OF FILE */
