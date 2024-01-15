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
#include "project.h"
struct st_imu_data {
    uint8 flags;        // Flags to know what we are reading (0/1) from each imu [ accel | gyro | magn | quat | temp ]
    int16 accel_value[3];
    int16 gyro_value[3];
    int16 temp_value;
};

extern struct st_imu_data g_imu, g_imuNew;
extern uint8 Mag[2][10][6];
extern uint8 Accel[2][10][6];
extern uint8 Gyro[2][10][6];
extern uint8 Temp[2];


/* [] END OF FILE */
