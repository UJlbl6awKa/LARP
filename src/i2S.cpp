/***********\ I2S AUDIO /***********/
#include "i2S.h"
void i2sStart()
{
  audioLogger = &Serial;
  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();
  out->SetGain(GAIN);
  out->SetPinout(Bit_Clock_BCLK, Word_Select_WS, Serial_Data_SD);
  aac->begin(in, out);
}