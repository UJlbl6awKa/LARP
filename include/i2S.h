/***********\ I2S AUDIO header file /***********/
#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "sampleaac.h"

#define Bit_Clock_BCLK 14
#define Word_Select_WS 13
#define Serial_Data_SD 12
#define GAIN 1

AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;

void i2sStart();