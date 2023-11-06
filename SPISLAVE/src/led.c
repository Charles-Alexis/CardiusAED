#include "led.h"


void setup_Slave() {
/* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)*/
    //printf("in setup slave");
    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_pad_select_gpio(BLINK_GPIO2);
    gpio_pad_select_gpio(SW2);
    gpio_pad_select_gpio(SW3);
    gpio_pad_select_gpio(SW4);
    gpio_pad_select_gpio(SW5);

    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT_OD);
    gpio_set_direction(BLINK_GPIO2, GPIO_MODE_OUTPUT_OD);
    gpio_set_direction(SW2, GPIO_MODE_INPUT);
    gpio_set_pull_mode(SW2,GPIO_PULLUP_ONLY);
    gpio_set_direction(SW3, GPIO_MODE_INPUT);
    gpio_set_direction(SW4, GPIO_MODE_INPUT);
    gpio_set_pull_mode(SW4,GPIO_PULLUP_ONLY);
    gpio_set_direction(SW5, GPIO_MODE_INPUT);
    gpio_set_level(BLINK_GPIO, 0);
}

void blink_task(void *pvParameter){

    int delay_time = 500;

    while(1) {


        if (!gpio_get_level(SW2))
        {
            delay_time = 125;
            //printf("SW2 ON\n");
        }
        else if (!gpio_get_level(SW3))
        {
            delay_time = 250;
            //printf("SW3 ON\n");
        }
        else if (!gpio_get_level(SW4))
        {
            delay_time = 500;
            //printf("SW4 ON\n");
        }
        else if (!gpio_get_level(SW5))
        {
            delay_time = 1000;
            //printf("SW5 ON\n");
        }

        /* Blink off (output low)*/ 
        gpio_set_level(BLINK_GPIO2, 0);
        //printf("LED_ON\n");
        vTaskDelay(delay_time / portTICK_PERIOD_MS);



         if (!gpio_get_level(SW2))
        {
            delay_time = 125;
            //printf("SW2 ON\n");
        }
        else if (!gpio_get_level(SW3))
        {
            delay_time = 250;
            //printf("SW3 ON\n");
        }
        else if (!gpio_get_level(SW4))
        {
            delay_time = 500;
            //printf("SW4 ON\n");
        }
        else if (!gpio_get_level(SW5))
        {
            delay_time = 1000;
            //printf("SW5 ON\n");
        }


        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO2, 1);
        //printf("LED_OFF\n");
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }

}
