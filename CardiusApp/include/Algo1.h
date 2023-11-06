#include <stdint.h>
#include <stdio.h> 
#include <stdbool.h>
#include <math.h>
#define ALGO1_BUFFER_SIZE 2500          //2500 samples
#define ALGO1_SAMPLE_IN_SECOND 250      //250 samples in 1 seconde




void Algo1_BandPassFilter(float* Data2Filter, float* DataFiltered);
//void Algo1_Count1Second(float* FilteredData1Sec, struct CountStruct *s); 
//bool Algo1_CheckIfShockable(struct CountStruct s, uint32_t BPM);
bool Algo1_CheckIfShockable(uint32_t *Value, uint32_t BPM);

//void Algo1_Counts(float* Data2Filter, struct CountStruct *s);
void Algo1_Counts(float* Data2Filter, uint32_t *c1, uint32_t *c2, uint32_t *c3, float *tresholdC1Low, float *tresholdC2Low, float *tresholdC3Low, float *tresholdC3High,float *DataFiltered);
uint8_t checkShock(uint32_t *c1, uint32_t *c2, uint32_t *c3);

float Algo1_Threshhold1(float *buff);
float Algo1_Threshhold2(float *buff);
float Algo1_Threshhold3(float *buff, float m);
void Algo1_Comput1Second(float *buff, uint32_t *Value, uint32_t SecondeIndex); 

