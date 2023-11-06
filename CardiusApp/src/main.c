//FREERTOS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "ComSPI.h"
#include "DechargeFunctions.h"

//Task Priority
#define adctaskPRIORITY (5)
#define blinktaskPRIORITY (6)
#define algo1taskPRIORITY (3)
#define sdcardtaskPRIORITY (1)

//INCLUDE TASK
#include "TaskFunction.h"
#include "AdcFunction.h"

//ADC EXTERN DEFENITION
extern int32_t temp_val;
extern int32_t adc_reading;
extern uint32_t AdcSampleIndex;
extern float RawDataBuff1[250];

//ALGO1
extern bool state;
extern bool flag_state;

//SDCARD
extern bool SDState;
extern float sdcardData;
extern bool FlagStateSD;

extern bool filtered;
extern bool stopflag;
extern float tempvalue;

extern float tempvalueC1;
extern float tempvalueC2;
extern float tempvalueC3;
extern float tempvalueC4;
extern float tempvalueC5;
extern float tempvalueC6;
extern float tempvalueC7;
extern float tempvalueC8;
extern float tempvalueC9;
extern float tempvalueC10;
extern uint8_t resultAlgo;

extern uint32_t tempvalueCT1;
extern uint32_t tempvalueCT2;
extern uint32_t tempvalueCT3;

//DEBUG
extern bool DEBUG;
extern bool Shock;
extern bool tempPrintShock;
extern uint8_t tempValue;
extern float Send2SPI;

extern int32_t debugAdc;
extern bool flagStartVSense; 
//DEBUG SPI REC
extern uint8_t r1;
extern float r2;
extern uint32_t r3;
extern uint8_t r4;
extern uint8_t r5;
extern uint8_t r6;

int temp=0;

int32_t returnTickFromMs(int time){return time/portTICK_PERIOD_MS;}

void app_main()
{
    TickType_t LWT;
    const TickType_t ADCFreq = 1000; //4 ticks = 4 ms
    InitGPIO();

    //xTaskCreate(&SDCard_Task, "SDCard_Task", 4096, "SDCard TASK", sdcardtaskPRIORITY, NULL);
    xTaskCreate(&Blink_Task, "Blink_Task", configMINIMAL_STACK_SIZE, "Blink Led TASK", blinktaskPRIORITY, NULL);
    xTaskCreate(&Speaker_Task, "Speaker_Task", 4096, "Speaker sound TASK", 8, NULL);
    xTaskCreate(&ADC_Task, "ADC_Task", configMINIMAL_STACK_SIZE, "ADC Get TASK", adctaskPRIORITY, NULL);
    //xTaskCreate(&Algo1_Task, "Algo1_Task", 8192, "Algo 1 TASK", 3, NULL);
    //xTaskCreate(&Send_Data_Task, "Send_Data_Task", 8192, "Send Data Task", 1, NULL);


    uint32_t temp = 0;
    uint8_t oldvalue = 0;
    while(1) {
        //DÉBUT DU CHRONO
        LWT = xTaskGetTickCount ();

        if(r1!=176 || r1!=0){
            printf("------------\n"); 
            printf("addr: %d\n",r1);
            printf("dataV: %f\n",r2);
            printf("data: %d\n",r3);
            printf("B1: %d\n",r4);
            printf("B2: %d\n",r5);
            printf("B3: %d\n",r6);
            printf("------------\n");
        }

        printf("C1 %d\n",tempvalueCT1);
        printf("C2 %d\n",tempvalueCT2);
        printf("C3 %d\n",tempvalueCT3);
        printf("------------\n");

        if(tempPrintShock == true){
                temp += 15;
                tempPrintShock = false;
                if(Shock == true){printf("SHOCK with %d at %d\n", tempValue,temp);}
                else{printf("PAS SHOCK with %d at %d\n", tempValue,temp);}
            }
        vTaskDelayUntil(&LWT, ADCFreq); 
        }
}


 