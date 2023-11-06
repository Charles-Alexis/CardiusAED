#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define SW1     GPIO_NUM_33
#define SW2     GPIO_NUM_12
#define SW3     GPIO_NUM_32
#define SW4     GPIO_NUM_27
#define R1      GPIO_NUM_25
#define R2      GPIO_NUM_17

void InitGPIO();
void SwitchToAcq();
void SwitchToCharge();
void StopToCharge();
void SwitchTointernal();
void SwitchToPatient();
void SwitchToTest3();
void SwitchToTest4();

void blinkGPIO(gpio_num_t GPIONUM);