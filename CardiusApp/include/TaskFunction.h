#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//GPIO
#include "driver/gpio.h"
#include "sdkconfig.h"
#define BLINK_GPIO 25

//ALGO
#include "Algo1.h"
void resetCountStruct(uint32_t *c1,uint32_t *c2,uint32_t *c3);


//SDCard
#include "SDCard.h"
#include "ComSPI.h"
#define DATALENGTH 32
void addToQueue(uint8_t index, float* buff, float * toAdd);

//Task Prototype
void ADC_Task(void *pvParameter);
void Blink_Task(void *pvParameter);
void Algo1_Task(void *pvParameter);
void SDCard_Task(void *pvParameter);
void Send_Data_Task(void *pvParameter);
void Speaker_Task(void *pvParameter);