// Includes
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/i2s.h"    

#define BLINK_GPIO 32
#define BLINK_GPIO2 33
#define SW2 12
#define SW5 25
#define SW4 26
#define SW3 27


void setup_Slave();
void blink_task(void *pvParameter);