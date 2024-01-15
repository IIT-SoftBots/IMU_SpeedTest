#include "QB_lib/commands.h"
#include "QB_lib/qbmove_communications.h"
#include "QB_lib/cp_commands.h"
#include "QB_lib/cp_communications.h"
#include "iostream"
#include <math.h>
#include <fstream>
#include <signal.h>
#include <sys/time.h>
#include <windows.h>
#include <unistd.h>
#include <chrono>
#include <ctime>

FILE* imu_file;
int cnt;
int index;
float tempo[1000000];
comm_settings comm_settings_t;
uint8_t aux_string[5000];
uint8_t PARAM_SLOT_BYTES = 50;
int num_of_params;
int n_imu;
uint8_t* ids;
uint8_t* imu_table;
uint8_t* mag_cal;
float* imu_values;
uint8_t num_imus_id_params = 7;
uint8_t num_mag_cal_params = 0;
uint8_t first_imu_parameter = 2;
uint8_t new_board = 1;
int i = 0 ,k = 0;
struct timeval newstart, stop;
int device_id = 1;
float acc_value[1000000][20];
int a;



/*void signal_callback_handler(int signum) {
	int gg;
   	closeRS485( &comm_settings_t );
   	for (gg = 0; gg < n_imu; gg++) {
		fprintf(imu_file,"ACC_X %d, ",ids[gg]);
		fprintf(imu_file,"ACC_Y %d, ",ids[gg]);
		fprintf(imu_file,"ACC_Z %d, ",ids[gg]);
	}
   		fprintf(imu_file,"Time[ms]\n");
   	for (gg=0;gg<cnt;gg++){
		for (index=0;index<n_imu*3;index++){
			fprintf(imu_file,"%f, ", acc_value[gg][index]);
		}
		fprintf(imu_file," --- %.03f\n",tempo[gg]);
	}
	fclose(imu_file);
   std::cout << "\nGuusnèstatoqui \n"  << std::endl;
   // Terminate program
      exit(signum);
}*/

int main(){
	// Register signal and signal handler
    //signal(SIGINT, signal_callback_handler);
	
    openRS485( &comm_settings_t , "COM14", 2000000) ;       // QB Board Opening

	usleep(500000);
	
	// ---- RETRIEVE IMU BOARD PARAMETER ----
	if (commGetIMUParamList(&comm_settings_t, device_id, 0, NULL, 0, 0, aux_string) < 0){
		// If commGetIMUParamList returns -1, the connected board is a PSoC3 board instead of a STM32 or PSoC5 board
		// so call the commGetParamList instead
		new_board = 0;
		commGetParamList(&comm_settings_t, device_id, 0, NULL, 0, 0, aux_string);
		num_imus_id_params = 6;
	}
	
	num_of_params = aux_string[5];
	
	//aux_string[6] <-> packet_data[2] on the firmware
	n_imu = aux_string[8];
	printf("Number of connected IMUs: %d\n", n_imu);
	
	// Compute number of read parameters depending on n_imu and
	// update packet_length
	num_mag_cal_params = (n_imu / 2);
	if ( (n_imu - num_mag_cal_params*2) > 0 ) num_mag_cal_params++;

	ids = (uint8_t *) calloc(n_imu, sizeof(uint8_t));
	i = 0;
	for (k = 1; k <= num_imus_id_params; k++){
		if (aux_string[k*PARAM_SLOT_BYTES + 8] != 255) {
			ids[i] = aux_string[k*PARAM_SLOT_BYTES + 8];
			i++;
		}
		if (aux_string[k*PARAM_SLOT_BYTES + 9] != 255) {
			ids[i] = aux_string[k*PARAM_SLOT_BYTES + 9];
			i++;
		}
		if (aux_string[k*PARAM_SLOT_BYTES + 10] != 255) {
			ids[i] = aux_string[k*PARAM_SLOT_BYTES + 10];
			i++;
		}
	}
	
	// Retrieve magnetometer calibration parameters
	mag_cal = (uint8_t *) calloc(n_imu, 3*sizeof(uint8_t));
	i = 0;
	for (k=1; k <= num_mag_cal_params; k++) {
		mag_cal[3*i + 0] = aux_string[num_imus_id_params*PARAM_SLOT_BYTES + k*PARAM_SLOT_BYTES + 8];
		mag_cal[3*i + 1] = aux_string[num_imus_id_params*PARAM_SLOT_BYTES + k*PARAM_SLOT_BYTES + 9];
		mag_cal[3*i + 2] = aux_string[num_imus_id_params*PARAM_SLOT_BYTES + k*PARAM_SLOT_BYTES + 10];
		printf("MAG PARAM: %d %d %d\n", mag_cal[3*i + 0], mag_cal[3*i + 1], mag_cal[3*i + 2]);
		i++;
		
		if (aux_string[num_imus_id_params*PARAM_SLOT_BYTES + k*PARAM_SLOT_BYTES + 7] == 6) {
			mag_cal[3*i + 0] = aux_string[num_imus_id_params*PARAM_SLOT_BYTES + k*PARAM_SLOT_BYTES + 11];
			mag_cal[3*i + 1] = aux_string[num_imus_id_params*PARAM_SLOT_BYTES + k*PARAM_SLOT_BYTES + 12];
			mag_cal[3*i + 2] = aux_string[num_imus_id_params*PARAM_SLOT_BYTES + k*PARAM_SLOT_BYTES + 13];
			printf("MAG PARAM: %d %d %d\n", mag_cal[3*i + 0], mag_cal[3*i + 1], mag_cal[3*i + 2]);
			i++;
		}
	}

	first_imu_parameter = 1 + num_imus_id_params + num_mag_cal_params + 1;
	imu_table = (uint8_t *) calloc(n_imu, 5*sizeof(uint8_t));
	for (i=0; i< n_imu; i++){
		imu_table[5*i + 0] = aux_string[first_imu_parameter*PARAM_SLOT_BYTES + 8 + 50*i];
		imu_table[5*i + 1] = aux_string[first_imu_parameter*PARAM_SLOT_BYTES + 9 + 50*i];
		imu_table[5*i + 2] = aux_string[first_imu_parameter*PARAM_SLOT_BYTES + 10 + 50*i];
		imu_table[5*i + 3] = aux_string[first_imu_parameter*PARAM_SLOT_BYTES + 11 + 50*i];
		imu_table[5*i + 4] = aux_string[first_imu_parameter*PARAM_SLOT_BYTES + 12 + 50*i];
		printf("ID: %d - %d, %d, %d, %d, %d\n", ids[i], imu_table[5*i + 0], imu_table[5*i + 1], imu_table[5*i + 2], imu_table[5*i + 3], imu_table[5*i + 4]);
		
	}
	
	// Imu values is a (3 sensors x 3 axes + 4 + 1) x n_imu values
	imu_values = (float *) calloc(n_imu, 3*3*sizeof(float)+4*sizeof(float)+sizeof(float));
	
	if (!new_board && n_imu > 1){
		int idx = 0;
		for (i = 0; i < n_imu; i++) {
			if (imu_table[5*i + 3]){
				idx++;
			}
			if (idx > 0) {
				printf("\n[WARNING] Quaternion will not be read as it is computed only if there is ONLY 1 IMU connected to the board.\n\n");
				return -1;
			}
		}
	}

	// ---- START CYCLING ----
	
	
	index=0;
	cnt=0;
	auto inizio = std::chrono::system_clock::now();
	auto end=inizio;
	std::chrono::duration<double> elapsed_mseconds_t = (end-inizio)*1000;
	
	while(elapsed_mseconds_t.count() < 1000 ){
		
		auto start = std::chrono::system_clock::now();
		commGetImuReadings(&comm_settings_t, device_id, imu_table, mag_cal, n_imu, imu_values);
		imu_file=fopen("./../imu_file.csv","w");
		end = std::chrono::system_clock::now(); 
		printf("\nIMU: %d\n", ids[i]);
		printf("\nIMU: %d\n", n_imu);
	
		for (i = 0; i < n_imu; i++) {
	
			printf("\nIMU: %d\n", ids[i]);
		
			//usleep(100);
			
			if (imu_table[5*i + 0]){
				
				acc_value[cnt][index]=imu_values[(3*3+4+1)*i];
				acc_value[cnt][index+1]=imu_values[(3*3+4+1)*i+1];
				acc_value[cnt][index+2]=imu_values[(3*3+4+1)*i+2];
				
		
				//printf("Accelerometer\n");
				printf("%f, %f, %f\n", imu_values[(3*3+4+1)*i], imu_values[(3*3+4+1)*i+1], imu_values[(3*3+4+1)*i+2]);

				//printf("%f,%f, %f\n", acc_value[cnt][index], acc_value[cnt][index+1], acc_value[cnt][index+2]);
			}	index=index+3;
					
		}

		index=0;
		std::chrono::duration<double> elapsed_mseconds = (end-start)*1000;
	    std::cout << "Cycle Elapsed time: " << elapsed_mseconds.count() << " ms"<< std::endl;

		elapsed_mseconds_t = (end-inizio)*1000;
	    std::cout << "Aquisition Elapsed time: " << elapsed_mseconds_t.count() << " ms"<< std::endl;
		//std::cout << "Elapsed time: " << tempo[cnt] << " ms"<< std::endl;
		//start = end;
		tempo[cnt]=elapsed_mseconds_t.count();
		cnt=cnt+1;
	}
	
	int gg;
   	closeRS485( &comm_settings_t );
   	for (gg = 0; gg < n_imu; gg++) {
		fprintf(imu_file,"ACC_X %d, ",ids[gg]);
		fprintf(imu_file,"ACC_Y %d, ",ids[gg]);
		fprintf(imu_file,"ACC_Z %d, ",ids[gg]);
	}
   		fprintf(imu_file,"Time[ms]\n");
   	for (gg=0;gg<cnt;gg++){
		for (index=0;index<n_imu*3;index++){
			fprintf(imu_file,"%f, ", acc_value[gg][index]);
		}
		fprintf(imu_file," --- %.03f\n",tempo[gg]);
	}
	fclose(imu_file);
   std::cout << "\nGuusnèstatoqui \n"  << std::endl;

    return 0;

}
