#include "Algo1.h"
#include <stdlib.h>

static float CoefU0 = 0.0625;
static float CoefU1 = 0;
static float CoefU2 = 0.0625;
static float CoefY0 = 1;
static float CoefY1 = 1.75;
static float CoefY2 = 0.875;

float InputU0 = 0;
float InputU1 = 0;
float InputU2 = 0;
float OuputY0 = 0;
float OuputY1 = 0;
float OuputY2 = 0;
float C1L = 0, C2L = 0, C3L = 0, C3H = 0;

bool tempc=false;
float tC1L = 0, tC2L = 0, tC3L = 0, tC3H = 0;

void Algo1_BandPassFilter(float* Data2Filter, float* DataFiltered)
{
    InputU0 = 0;
    InputU1 = 0;
    InputU2 = 0;
    OuputY0 = 0;
    OuputY1 = 0;
    OuputY2 = 0;
    for(uint32_t i = 0; i<ALGO1_BUFFER_SIZE ;i++)
        {
            InputU2 = InputU1;
            InputU1 = InputU0;
            InputU0 = Data2Filter[i];

            OuputY2 = OuputY1;
            OuputY1 = OuputY0;
            OuputY0 = (CoefY1*OuputY1) - (CoefY2 * OuputY2) + (CoefU0*(InputU0-InputU2));
            DataFiltered[i] = fabs(OuputY0);
        }
}

void Algo1_Counts(float* Data2Filter, uint32_t *c1, uint32_t *c2, uint32_t *c3, float *tresholdC1Low, float *tresholdC2Low, float *tresholdC3Low, float *tresholdC3High, float *DataFiltered){
    Algo1_BandPassFilter(Data2Filter,DataFiltered);
    float md=0;
    float tempData[250];
    for(uint32_t i = 0; i<10; i++){

        
        for(uint32_t k = 0; k<ALGO1_SAMPLE_IN_SECOND; k++){
            tempData[k] = fabs(DataFiltered[ ((i*ALGO1_SAMPLE_IN_SECOND)+k)]);
        }

        tresholdC1Low[i] = Algo1_Threshhold1(tempData);
        tresholdC2Low[i] = Algo1_Threshhold2(tempData);
        md =               Algo1_Threshhold3(tempData,tresholdC2Low[i]);
        tresholdC3Low[i] = tresholdC2Low[i]-md;
        tresholdC3High[i] = tresholdC2Low[i]+md;

        for(uint32_t j =0 ; j<ALGO1_SAMPLE_IN_SECOND;j++){
            if(tempData[j]>=tresholdC1Low[i]){(c1[0])++;}
            if(tempData[j]>=tresholdC2Low[i]){(c2[0])++;}
            if((tempData[j]>=tresholdC3Low[i]) && (tempData[j]<=tresholdC3High[i])){(c3[0])++;}
        }

    }
}

uint8_t checkShock(uint32_t *c1, uint32_t *c2, uint32_t *c3)
{
    uint8_t shock=0;
    if(c1[0] < 250 && c2[0] > 950 && ((c1[0]*c2[0])/c3[0])<210){shock = 1;}
    if(c1[0] >= 250 && c2[0] && c2[0] > 600 && ((c1[0]*c2[0])/c3[0])<210){shock = 1;}
    if(c1[0] >= 250 && c2[0] > 950){shock = 1;}
    if(c2[0] > 1100){shock = 1;}
    return shock;
}


float Algo1_Threshhold1(float *buff){
    float MAX=0;
    for(uint32_t i = 0; i<ALGO1_SAMPLE_IN_SECOND ;i++){if(buff[i]>MAX){MAX = buff[i];}} 
    MAX = MAX/(float)2;
    return MAX;
}

float Algo1_Threshhold2(float *buff){
    float MEAN=0;
    for(uint32_t i = 0; i<ALGO1_SAMPLE_IN_SECOND; i++){MEAN+=buff[i];}
    MEAN = MEAN/(float)ALGO1_SAMPLE_IN_SECOND; 
    return MEAN;
}

float Algo1_Threshhold3(float *buff, float M){
    float MD = 0;
    for(uint32_t i = 0; i<ALGO1_SAMPLE_IN_SECOND ;i++)
        {
            MD += fabs(buff[i] - M);
        } 
        MD = MD/(float)ALGO1_SAMPLE_IN_SECOND;
    return MD;
}

void Algo1_Comput1Second(float *buff, uint32_t *Value, uint32_t SecondeIndex){
    int32_t Value1 = 0, Value2=0, Value3=0;
    float max = Algo1_Threshhold1(buff);
    float mean = Algo1_Threshhold2(buff);
    float md = Algo1_Threshhold3(buff,mean);
    for(uint32_t i = 0; i<ALGO1_SAMPLE_IN_SECOND ;i++)
        {
            if(buff[i] > max){Value1++;}
            if(buff[i] > mean){Value2++;}
            if(buff[i] > (mean-md) && buff[i] < (mean+md)){Value3++;}
        } 
    Value[(SecondeIndex*3)] = Value1;
    Value[(SecondeIndex*3)+1] = Value2;
    Value[(SecondeIndex*3)+2] = Value3;
}

bool Algo1_CheckIfShockable(uint32_t *Value, uint32_t BPM)
{
    if(Value[30] < 250 && Value[31] > 950 && ((Value[30]*Value[31])/Value[32])<210){return true;}
    if(Value[30] >= 250 && Value[30] && Value[31] > 600 && ((Value[30]*Value[31])/Value[32])<210){return true;}
    if(Value[30] >= 250 && Value[31] > 950){return true;}
    if(Value[31] > 1100){return true;}
    if(BPM >= 180){return true;}
    return false;
}