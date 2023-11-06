#include "Algo1.h"
#include <stdlib.h>

static float CoefU0 = 0.0625;
static float CoefU1 = 0;
static float CoefU2 = 0.0625;
static float CoefY0 = 1;
static float CoefY1 = 1.75;
static float CoefY2 = 0.875;

float TempU0 = 0;
float TempU1 = 0;
float TempU2 = 0;
float TempY0 = 0;
float TempY1 = 0;
float TempY2 = 0;
float C1L = 0, C2L = 0, C3L = 0, C3H = 0;

bool tempc=false;
float tC1L = 0, tC2L = 0, tC3L = 0, tC3H = 0;

void Algo1_BandPassFilter(float* Data2Filter)
{
    TempU0 = 0;
    TempU1 = 0;
    TempU2 = 0;
    TempY0 = 0;
    TempY1 = 0;
    TempY2 = 0;
    for(uint32_t i = 0; i<ALGO1_BUFFER_SIZE ;i++)
        {
            TempU2 = TempU1;
            TempU1 = TempU0;
            TempU0 = Data2Filter[i];

            TempY2 = TempY1;
            TempY1 = TempY0;
            TempY0 = (CoefY1*TempY1) - (CoefY2 * TempY2) + (CoefU0*(TempU0-TempU2));
            Data2Filter[i] = fabs(TempY0);
        }
}

void Algo1_Counts(float* Data2Filter, uint32_t *c1, uint32_t *c2, uint32_t *c3, float *tresholdC1Low, float *tresholdC2Low, float *tresholdC3Low, float *tresholdC3High){
    Algo1_BandPassFilter(Data2Filter);
    float md=0;
    float tempData[250];
    for(uint32_t i = 0; i<10; i++){
        for(uint32_t k = 0; k<250; k++){
            tempData[k] = Data2Filter[((i*250)+k)];
        }

        tresholdC1Low[i] = Algo1_Threshhold1(tempData);
        tresholdC2Low[i] = Algo1_Threshhold2(tempData);
        md = Algo1_Threshhold3(tempData,tresholdC1Low[i]);
        tresholdC3Low[i] = tresholdC1Low[i]-md;
        tresholdC3High[i] = tresholdC1Low[i]+md;

        for(uint32_t j = i*ALGO1_SAMPLE_IN_SECOND; j<((i+1)*ALGO1_SAMPLE_IN_SECOND);j++){
            if(Data2Filter[j]>=tresholdC1Low[i]){(c1[0])++;}
            if(Data2Filter[j]>=tresholdC2Low[i]){(c2[0])++;}
            if((Data2Filter[j]>=tresholdC3Low[i]) && (Data2Filter[j]<=tresholdC3High[i])){(c3[0])++;}
        }

    }
}
/*
void Algo1_Count1Second(float* FilteredData1Sec, struct CountStruct *s)
{
    
    C1L = 0, C2L = 0, C3L = 0, C3H = 0;
    float mean=0;

    for(uint32_t i = 0; i<ALGO1_SAMPLE_IN_SECOND ;i++)
    {
        mean = mean+FilteredData1Sec[i];
        if(FilteredData1Sec[i]>C1L){C1L = FilteredData1Sec[i];}
    }

    C1L /= 2;
    mean /= ALGO1_SAMPLE_IN_SECOND;
    C2L=mean;
    float MD = 0;
    for(uint32_t i = 0; i<ALGO1_SAMPLE_IN_SECOND ;i++){
         MD = MD + abs(FilteredData1Sec[i] - mean);
    }
    MD /= ALGO1_SAMPLE_IN_SECOND;
    C3L = mean-MD;
    C3H = mean+MD;

    for(uint32_t i = 0; i<ALGO1_SAMPLE_IN_SECOND ;i++)
    {
        if(FilteredData1Sec[i]>C1L){s->c1++;}
        if(FilteredData1Sec[i]>C2L){s->c2++;}
        if(FilteredData1Sec[i]>C3L && FilteredData1Sec[i]<C3L){s->c3++;}
    }
    if(tempc==false){
        tC1L = C1L; 
        tC2L = C2L;
        tC3L = C3L;
        tC3H = C3H;
        tempc =true;
    }
}*/

/*
bool Algo1_CheckIfShockable(struct CountStruct s, uint32_t BPM)
{
    if(s.c1 < 250 && s.c2>950 && ((s.c1*s.c2)/s.c3)<210){return true;}
    if(s.c1 >= 250 && s.c1<400 && ((s.c1*s.c2)/s.c3)<210){return true;}
    if(s.c1 >= 250 && s.c2>950){return true;}
    if(s.c2>1100){return true;}
    if(BPM >= 180){return true;}
    return false;
}*/

float Algo1_Threshhold1(float *buff){
    float MAX=0.1;
    for(uint32_t i = 0; i<ALGO1_SAMPLE_IN_SECOND ;i++){if(buff[i]>MAX){MAX = buff[i];}} 
    MAX = MAX/2;
    return MAX;
}

float Algo1_Threshhold2(float *buff){
    float MEAN=0;
    for(uint32_t i = 0; i<ALGO1_SAMPLE_IN_SECOND ;i++){MEAN = MEAN+buff[i];}
    MEAN = MEAN/ALGO1_SAMPLE_IN_SECOND; 
    return MEAN;
}

float Algo1_Threshhold3(float *buff, float M){
    float MD = 0;
    for(uint32_t i = 0; i<ALGO1_SAMPLE_IN_SECOND ;i++)
        {
            MD = MD + fabs(buff[i] - M);
        } 
        MD = MD/ALGO1_SAMPLE_IN_SECOND;
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