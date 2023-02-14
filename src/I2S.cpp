/*#include <Arduino.h>
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

void I2S_setup() {
  audioLogger = &Serial;
  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();
  out->SetGain(GAIN);
  out->SetPinout(Bit_Clock_BCLK, Word_Select_WS, Serial_Data_SD);
  aac->begin(in, out);
}


void I2S_play() {
  if (aac->isRunning()) {
    aac->loop();
  }
}*/