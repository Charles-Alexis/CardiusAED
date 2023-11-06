#include "TaskFunction.h"
#include "AdcFunction.h"
#include "DechargeFunctions.h"
#include "Speaker.h"
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
float tempvalueC5 = 0;
float tempvalueC6 = 0;
float tempvalueC7 = 0;
float tempvalueC8 = 0;
float tempvalueC9 = 0;
float tempvalueC10 = 0;


uint32_t tempvalueCT1 = 0;
uint32_t tempvalueCT2 = 0;
uint32_t tempvalueCT3 = 0;
uint8_t resultAlgo = 0;

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
float DataFiltered[2500];
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
int32_t debugAdc = 0;

//SPI
float Send2SPI=0;
uint8_t r1=0;
float r2=0;
uint32_t r3=0;
uint8_t r4=0;
uint8_t r5=0;
uint8_t r6=0;

//Result
bool Shock = false;
bool tempPrintShock = false;
uint8_t tempValue = false;

//Charge Sequence
bool flagStartVSense = false;

//SPEAKER
bool flagSpeaker = false;


void ADC_Task(void *pvParameter)
{
    TickType_t LWT;
    const TickType_t ADCFreq = 50; //4 ticks = 4 ms

    //INTIALISE ADC
    adc1_config_width(ADC_WIDTH_BIT_12); //12 BIT
    adc1_config_channel_atten(channel, atten); //GPIO34, 0DB Attenuation 
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    int32_t voltage=0;
    while (1) 
        {
            //DÉBUT DU CHRONO
            LWT = xTaskGetTickCount ();

            //if(flagStartVSense==false){
                //LECTURE ADC
                adc_reading = adc1_get_raw(channel);
                voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
                debugAdc=adc_reading;
                if(adc_reading>(2700/1)){
                    flagStartVSense=true;
                }
            //}
            //FIN DU CHRONO
            vTaskDelayUntil(&LWT, ADCFreq); //Waiting 4 ticks from LWT tick count
        }
}

void Algo1_Task(void *pvParameter)
{
    //INITILISATION DES VALEURS
    TickType_t LWT;
    uint8_t result = 0;
    uint8_t resultIndex = 0;
    uint32_t testI = 0;
    bool filtered = false;
    const TickType_t ADCFreq = 50; //4 ticks = 4 ms
    while(1){
        LWT = xTaskGetTickCount ();   
        if(stopflag == true){
            stopflag = false;
            Algo1_Counts(Data2Analyse, count1, count2, count3, tresholdC1Low, tresholdC2Low, tresholdC3Low, tresholdC3High,DataFiltered);
            tempvalueCT1 = count1[0];
            tempvalueCT2 = count2[0];
            tempvalueCT3 = count3[0];

            result = result + checkShock(count1, count1, count3);

            count1[0] = 0;
            count2[0] = 0;
            count3[0] = 0;


            resultAlgo = result;
            resultIndex ++;

            if(resultIndex==15){
                resultIndex=0;
                if(result > 14){
                    Shock = true;
                }
                else{
                    Shock = false;
                }
                tempValue = result;
                tempPrintShock = true;
                result = 0;
            }
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
    const TickType_t ADCFreq = 4; //4 ticks = 4 ms
    uint8_t paquetsLoaded = 0;

    while(1){
        LWT = xTaskGetTickCount ();                 //Get Current Tick Count

        fgets(line, sizeof(line), f_S);
        temp = atof(line);
        Send2SPI = temp;
        TempBuff[sdcardSample] = temp;
        sdcardSample++;

        if(sdcardSample==250){
            addToQueue(paquetsLoaded, Data2Analyse, TempBuff);
            if(paquetsLoaded!=10){paquetsLoaded++;}
            else{stopflag = true;}
            sdcardSample=0;
        }
        vTaskDelayUntil(&LWT, ADCFreq);
    }
}

void addToQueue(uint8_t index, float* buff, float * toAdd){
    uint32_t tempLow = (index) * 250;
    uint32_t tempHigh = ((index+1) * 250);
    uint32_t indexToAdd = 0;
    if(index!=10) {                                                  
            for(uint32_t i = tempLow; i < tempHigh ; i++){
                buff[i] = toAdd[indexToAdd];
                indexToAdd++;
            }
        }
    else{
            for(uint32_t i = 0; i <= 2249; i++){buff[i] = buff[(i+250)];}
            uint32_t indexY = 0;
            for(uint32_t i = 2250; i < 2499; i++){buff[i] = toAdd[indexY];indexY++;}
        }

}


void Blink_Task(void *pvParameter)
{
    TickType_t LWT;
    const TickType_t ADCFreq = 1000; 
    gpio_num_t BLINK_GPIO1 = GPIO_NUM_25;
    bool test1 = false;
    while(1){

        if(test1 == false){
            //Switch to ACQ
            SwitchToAcq();

            //WAIT 5 sec
            LWT = xTaskGetTickCount ();  
            vTaskDelayUntil(&LWT, 5000);

            //Start charge
            SwitchToCharge();
            //Wait until adc Return true
            while(flagStartVSense == false){
                LWT = xTaskGetTickCount ();  
                vTaskDelayUntil(&LWT, 20);
            }
            flagSpeaker = true;
            //Instantly stop the charge
            StopToCharge();

            //WAIT 5 secondes
            LWT = xTaskGetTickCount ();  
            vTaskDelayUntil(&LWT, 5000);

            //Start to decharge to internal
            SwitchToPatient();

            //WAIT 5 sec
            LWT = xTaskGetTickCount ();  
            vTaskDelayUntil(&LWT, 5000);
            test1=true;
        }
            LWT = xTaskGetTickCount ();  
            vTaskDelayUntil(&LWT, 1000);

    }
}

void Speaker_Task(void *pvParameter)
{
    TickType_t LWT;
    const TickType_t freq = 500; 
    setup_Master();
    while(1){
        if(flagSpeaker==true){
                play();
                flagSpeaker = false;
            }
        LWT = xTaskGetTickCount ();  
        vTaskDelayUntil(&LWT, freq);
    }
}


void Send_Data_Task(void *pvParameter)
{
    TickType_t LWT;
    const TickType_t ADCFreq = 1000; 
    //const TickType_t ADCFreq = 2;  // FOR ALGO
    spi_device_handle_t spi = InitSPIComm();
    WORD_ALIGNED_ATTR uint8_t recbuf[4];
    WORD_ALIGNED_ATTR uint8_t tempuintFC[4]= {138,223,254,0}; //frameControl
    LWT = xTaskGetTickCount ();  
    send_data(spi, tempuintFC, 4, recbuf);
    vTaskDelayUntil(&LWT, ADCFreq);

    WORD_ALIGNED_ATTR uint8_t tempuinCRF[4]= {133,32,0,12}; //CommandRefControl
    LWT = xTaskGetTickCount ();  
    send_data(spi, tempuinCRF, 4, recbuf);
    vTaskDelayUntil(&LWT, ADCFreq);

    WORD_ALIGNED_ATTR uint8_t tempuinEC[4]= {129,224,4,14}; //ECGControl
    LWT = xTaskGetTickCount ();  
    send_data(spi, tempuinEC, 4, recbuf);
    vTaskDelayUntil(&LWT, ADCFreq);

    WORD_ALIGNED_ATTR uint8_t tempuinSF[4]= {64,0,0,0}; //StartFrame
    LWT = xTaskGetTickCount ();  
    send_data(spi, tempuinSF, 4, recbuf);
    vTaskDelayUntil(&LWT, ADCFreq);

    float valueV = 0;
    uint32_t sampleIndex = 0;
    uint8_t paquetsLoaded = 0;

    while(1) {
        uint8_t tempuinStart[4]= {0,0,0,0}; //StartFrame
        LWT = xTaskGetTickCount ();  
        long dataV = 0;

        send_data(spi, tempuinStart, 4, recbuf);

        dataV = ((long)recbuf[1] << 16) | ((long)recbuf[2] << 8) | ((long)recbuf[3]);
        
        valueV = (float)dataV * 0.00000008940697; //r2 = (float)dataV * (float)(  (2*1.8/2.4) / ((2^24)-1)  );
        TempBuff[sampleIndex] = valueV;
        r1 = recbuf[0];
        r2 = valueV;
        r3 = dataV;
        r4 = recbuf[1];
        r5 = recbuf[2];
        r6 = recbuf[3];

        
        // ADD TO ALGO BUFFER
        sampleIndex++;
        if(sampleIndex==250){
            addToQueue(paquetsLoaded, Data2Analyse, TempBuff);
            if(paquetsLoaded!=10){paquetsLoaded++;}
            else{stopflag = true;}
            sampleIndex=0;
        }


        vTaskDelayUntil(&LWT, ADCFreq);
    }
}