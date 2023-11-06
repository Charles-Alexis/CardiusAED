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

extern uint32_t tempvalueCT1;
extern uint32_t tempvalueCT2;
extern uint32_t tempvalueCT3;

//DEBUG
extern bool DEBUG;

// int temp=0;

int32_t returnTickFromMs(int time){return time/portTICK_PERIOD_MS;}

void app_main()
{
    TickType_t LWT;
    const TickType_t ADCFreq = 100; //4 ticks = 4 ms


    // xTaskCreate(&SDCard_Task, "SDCard_Task", 4096, "SDCard TASK", sdcardtaskPRIORITY, NULL);
    //xTaskCreate(&Blink_Task, "Blink_Task", configMINIMAL_STACK_SIZE, "Blink Led TASK", blinktaskPRIORITY, NULL);
    //xTaskCreate(&ADC_Task, "ADC_Task", configMINIMAL_STACK_SIZE, "ADC Get TASK", adctaskPRIORITY, NULL);
    // xTaskCreate(&Algo1_Task, "Algo1_Task", 4096, "Algo 1 TASK", algo1taskPRIORITY, NULL);

    // xTaskCreate(&Send_Data_Task, "Send_Data_Task", 4096, "Send Data Task", 1, NULL);
    // spi_device_handle_t spi = InitSPIComm();

    InitSPICommSlave();
    spi_slave_transaction_t transaction;

    WORD_ALIGNED_ATTR uint8_t sendbuf[4]={0};
    WORD_ALIGNED_ATTR uint8_t recvbuf[4]={0};
    memset(recvbuf, 0, sizeof(recvbuf));

    memset(&transaction, 0, sizeof(transaction));
    esp_err_t ret;
        

    while(1) {
        // LWT = xTaskGetTickCount ();

        transaction.length    = sizeof(recvbuf)*8;
        transaction.tx_buffer = sendbuf;             
        transaction.rx_buffer = recvbuf; 
        printf("-------------Waiting for master data-------------\n");



        ret = spi_slave_transmit(VSPI_HOST, &transaction, portMAX_DELAY);

        printf("Received1: %u\n",recvbuf[0]);
        printf("Received2: %u\n",recvbuf[1]);
        printf("Received3: %u\n",recvbuf[2]);
        printf("Received4: %u\n",recvbuf[3]);


        sendbuf[0] = recvbuf[0];
        sendbuf[1] = recvbuf[1];
        sendbuf[2] = recvbuf[2];
        sendbuf[3] = recvbuf[3];

        printf("Sended1: %u\n", sendbuf[0]);
        printf("Sended1: %u\n", sendbuf[1]);
        printf("Sended1: %u\n", sendbuf[2]);
        printf("Sended1: %u\n", sendbuf[3]);
        printf("Transaction Length: %d\n",transaction.trans_len);
        if (ret==ESP_OK) {
            printf("-------------End of main loop-------------\n");
        }
        // memset(recvbuf, 0, 1);
        // vTaskDelayUntil(&LWT, ADCFreq);
        }
}


