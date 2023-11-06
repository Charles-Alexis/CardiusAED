//------------------------------------------------------------------------------------------------------------------------
// Includes
    #include <stdio.h>
    #include <string.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "driver/gpio.h"
    #include "driver/i2s.h"                       // Library of I2S routines, comes with ESP32 standard install



//------------------------------------------------------------------------------------------------------------------------
    


#define ShutDownAudio 18
#define Device_detection_IO 26
#define Master 1
#define Slave 0


void setup_Master();
void play();
bool Device_detection();
