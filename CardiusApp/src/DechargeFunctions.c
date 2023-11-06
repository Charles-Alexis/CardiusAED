#include "DechargeFunctions.h"

void InitGPIO(){
    
    gpio_pad_select_gpio(SW1);
    gpio_set_direction(SW1, GPIO_MODE_OUTPUT);
    
    gpio_pad_select_gpio(SW2);
    gpio_set_direction(SW2, GPIO_MODE_OUTPUT);
    gpio_set_level(SW2,1);
    
    gpio_pad_select_gpio(SW3);
    gpio_set_direction(SW3, GPIO_MODE_OUTPUT);
    
    gpio_pad_select_gpio(SW4);
    gpio_set_direction(SW4, GPIO_MODE_OUTPUT);
    
    gpio_pad_select_gpio(R1);
    gpio_set_direction(R1, GPIO_MODE_OUTPUT);
    
    gpio_pad_select_gpio(R2);
    gpio_set_direction(R2, GPIO_MODE_OUTPUT);
}

void blinkGPIO(gpio_num_t GPIONUM){
    if(gpio_get_level(GPIONUM)==1){gpio_set_level(GPIONUM, 0);}
    else{gpio_set_level(GPIONUM, 1);}
}

void SwitchToAcq(){
    gpio_set_level(SW1,0);
    gpio_set_level(SW2,1);
    gpio_set_level(SW3,0);
    gpio_set_level(SW4,0);
    gpio_set_level(R1,0);
    gpio_set_level(R2,0);
}

void SwitchToCharge(){
    gpio_set_level(SW2,1);
    gpio_set_level(SW3,0);
    gpio_set_level(SW4,0);
    gpio_set_level(R2,0);

    // R1 BEFORE SW1
    TickType_t LWT = xTaskGetTickCount ();
    gpio_set_level(R1,1);
    vTaskDelayUntil(&LWT, 5); //TODO: switch time, not sure about 5ms
    gpio_set_level(SW1,1);
}

void StopToCharge(){
    
    gpio_set_level(SW1,0);

    TickType_t LWT = xTaskGetTickCount ();
    gpio_set_level(R1,0);
    vTaskDelayUntil(&LWT, 5); //TODO: switch time, not sure about 5ms

    gpio_set_level(SW2,1);
    gpio_set_level(SW3,0);
    gpio_set_level(SW4,0);
    gpio_set_level(R2,0);
}

void SwitchTointernal(){
    gpio_set_level(SW1,0);
    gpio_set_level(R1,0);
    gpio_set_level(SW2,0); // INTERNAL
    
    gpio_set_level(SW3,0);
    gpio_set_level(SW4,0);
    gpio_set_level(R2,0);
}

void SwitchToPatient(){
    gpio_set_level(SW2,1); // ???????????? DÉCHARGE INTERNE
    gpio_set_level(SW1,0);
    gpio_set_level(R1,0);
    gpio_set_level(R2,1);


    
    TickType_t LWT = xTaskGetTickCount ();
    gpio_set_level(SW3,1);
    vTaskDelayUntil(&LWT, 5); //TODO: SwITCH TIME LENGTH

    gpio_set_level(SW3,0);

    LWT = xTaskGetTickCount ();
    vTaskDelayUntil(&LWT, 1); //TODO: TIME BETWEEN PHASE

    LWT = xTaskGetTickCount ();
    gpio_set_level(SW4,1);
    vTaskDelayUntil(&LWT, 15); //TODO: SwITCH TIME LENGTH
    gpio_set_level(SW4,0);
}


void SwitchToTest3(){
    gpio_set_level(SW2,1); // ???????????? DÉCHARGE INTERNE
    gpio_set_level(SW1,0);
    gpio_set_level(R1,0);
    gpio_set_level(R2,0);
    gpio_set_level(SW4,0);
    gpio_set_level(SW3,1);
}

void SwitchToTest4(){
    gpio_set_level(SW2,1); // ???????????? DÉCHARGE INTERNE
    gpio_set_level(SW1,0);
    gpio_set_level(R1,0);
    gpio_set_level(R2,0);
    gpio_set_level(SW3,0);
    gpio_set_level(SW4,1);
}