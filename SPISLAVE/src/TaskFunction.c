#include "TaskFunction.h"
#include "AdcFunction.h"
#include <math.h>

//struct CountStruct Counter = {0,0,0};

//ADC
float RawDataBuff1[ALGO1_SAMPLE_IN_SECOND];
bool RawDataBuff1Fill = false;
float RawDataBuff2[ALGO1_SAMPLE_IN_SECOND];
bool RawDataBuff2Fill = false;
int32_t temp_val;
uint32_t AdcSampleIndex = 0;
int32_t adc_reading;

//AGLO1
bool state = false;
bool flag_state = false;
bool filtered = false;

//ALGO 1 Seconde
uint32_t ValeurSeconde[33];
uint32_t IndexSeconde = 0;

float tempvalueC1 = 0;
float tempvalueC2 = 0;
float tempvalueC3 = 0;
float tempvalueC4 = 0;

uint32_t tempvalueCT1 = 0;
uint32_t tempvalueCT2 = 0;
uint32_t tempvalueCT3 = 0;

uint32_t count1[1];
uint32_t count2[1];
uint32_t count3[1];
float tresholdC1Low[10];
float tresholdC2Low[10];
float tresholdC3Low[10];
float tresholdC3High[10];

//SDCARD
float TempBuff[250];
float Data2Analyse[2500];
bool TempBuffFill = false;
uint32_t sdcardSample = 0;
float sdcardData=0;
bool SwitchFlag = true;
bool FlagStateSD = false;
bool SDState = false;

float tempvalue = 0;
uint32_t tempindex = 0;
bool stopflag = false;

bool AlgoEnd = false;
float temp1;
float temp2;
float temp3;

//DEBUG
bool DEBUG = false;

void ADC_Task(void *pvParameter)
{
    TickType_t LWT;
    const TickType_t ADCFreq = 1; //4 ticks = 4 ms

    //INTIALISE ADC
    adc1_config_width(ADC_WIDTH_BIT_12); //12 BIT
    adc1_config_channel_atten(channel, atten); //GPIO34, 0DB Attenuation 
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    int32_t voltage;
    while (1) 
        {
            //DÉBUT DU CHRONO
            LWT = xTaskGetTickCount ();

            //LECTURE ADC
            adc_reading = adc1_get_raw(ADC_CHANNEL_6);
            voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
            
            //BUFFER1 OU BUFFER2
            if(RawDataBuff1Fill==false){RawDataBuff1[AdcSampleIndex] =adc_reading;}
            else if(RawDataBuff2Fill==false){RawDataBuff2[AdcSampleIndex] =adc_reading;}

            //INCRÉMENTE INDEX
            AdcSampleIndex++;

            //CHANGE STATUS DES BUFFER
            if(AdcSampleIndex == 250){
                if(RawDataBuff1Fill==false){RawDataBuff1Fill = true; RawDataBuff2Fill = false;}
                else if(RawDataBuff2Fill==false){RawDataBuff2Fill = true;RawDataBuff1Fill = false;}
                AdcSampleIndex = 0;
            }
            
            //FIN DU CHRONO
            vTaskDelayUntil(&LWT, ADCFreq); //Waiting 4 ticks from LWT tick count
        }
}

void Algo1_Task(void *pvParameter)
{
    //INITILISATION DES VALEURS
    TickType_t LWT;
    const TickType_t ADCFreq = 10; //4 ticks = 4 ms
    int divisionTemp = 0;
    while(1){
        LWT = xTaskGetTickCount ();   
        
        if((stopflag == true) && (filtered == false)){
            Algo1_Counts(Data2Analyse, count1, count2, count3, tresholdC1Low, tresholdC2Low, tresholdC3Low, tresholdC3High);
            filtered = true;
        }
        if((stopflag == true) && (filtered == true)){
            divisionTemp = tempindex/250;
            tempvalue = Data2Analyse[tempindex];
            tempvalueC1 = tresholdC1Low[divisionTemp];
            tempvalueC2 = tresholdC2Low[divisionTemp];
            tempvalueC3 = tresholdC3Low[divisionTemp];
            tempvalueC4 = tresholdC3High[divisionTemp];

            tempvalueCT1 = count1[0];
            tempvalueCT2 = count2[0];
            tempvalueCT3 = count3[0];

            tempindex++;
            if(tempindex == 2500){tempindex = 0;}
        }
        
        vTaskDelayUntil(&LWT, ADCFreq);
    }
}

void SDCard_Task(void *pvParameter)
{
    InitSDCard();
    float temp=0;
    char line[DATALENGTH];
    FILE* f_S = fopen("/sdcard/ATM426.txt", "r");
    TickType_t LWT;
    const TickType_t ADCFreq = 10; //4 ticks = 4 ms
    uint8_t paquetsLoaded = 0;

    while(1){
        LWT = xTaskGetTickCount ();                 //Get Current Tick Count

        if(stopflag==false){
            fgets(line, sizeof(line), f_S);
            temp = atof(line);
            TempBuff[sdcardSample] = temp;
            sdcardSample++;

            if(sdcardSample==250){
                addToQueue(paquetsLoaded, Data2Analyse, TempBuff);
                if(paquetsLoaded!=10){paquetsLoaded++;}
                sdcardSample=0;}

            if(paquetsLoaded==10){stopflag = true;}
        }/*
        else{
            tempvalue = Data2Analyse[tempindex];    
            tempindex++;
            if(tempindex == 2500){tempindex = 0;}       
        }*/
  
        vTaskDelayUntil(&LWT, ADCFreq);

    }

}

void addToQueue(uint8_t index, float* buff, float * toAdd){
    uint32_t temp = (index-1) * 250;
    if(index!=10) {                                                  //  [.......[.]..] index = 8
            for(uint32_t i = temp; i < temp+250 ; i++){buff[i] = toAdd[(i-temp)];}
        }

    else{
            for(uint32_t i = 0; i <= 2250; i++){buff[(2499-i)] = buff[(2249-i)];}
            for(uint32_t i = 0; i < 250; i++){buff[i]= toAdd[i];}
        }

}


void Blink_Task(void *pvParameter)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 1000;
    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    xLastWakeTime = xTaskGetTickCount();
    while(1) {
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}





void resetCountStruct(uint32_t *c1,uint32_t *c2,uint32_t *c3){
    (*c1) = 0;
    (*c2) = 0;
    (*c3) = 0;
}

void Send_Data_Task(void *pvParameter)
{
    TickType_t LWT;
    const TickType_t ADCFreq = 10; 
    spi_device_handle_t spi = InitSPICommMaster();
    // uint16_t tmp[4] = {1,2,3,4};
    
    while(1) {
        
        LWT = xTaskGetTickCount ();  

        send_cmd(spi, 0x04);
        vTaskDelayUntil(&LWT, ADCFreq);
    }
}