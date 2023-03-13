#include "LARP.h"

Adafruit_NeoPixel strip(17, 15); // количество светодиодов и пин

// millis
unsigned long prev_millis = 0;

void setup()
{
  Serial.begin(115200); // UART

  htmlStart();        // подключение к wi-fi 

  delay(1000);

  handleRoot();       // запуск сервера
  uwbSetup();         // настройка dw1000
  i2sStart();         // запуск I2S
  strip.begin();      // настройка светодиодки

}

void loop()
{
  // опрос датчика
  if (millis() - prev_millis >= 10)
  {
    prev_millis = millis();

    DW1000Ranging.loop();
    server.handleClient();

    if (DW1000Ranging.getDistantDevice()->getRange() <= 0.5)
    {
      ledFlag = true;
      I2SFlag = true;
    }
    else
    {
      ledFlag = false;
      I2SFlag = false;
    }

    if (ledFlag & ledMask)
    {
      for (uint8_t i; i <= strip.numPixels(); i++)
      {
        strip.setPixelColor(i, 0, 128, 0);
      }
      strip.show();
    }
    else
    {
      for (uint8_t i; i <= strip.numPixels(); i++)
      {
        strip.setPixelColor(i, 0, 0, 0);
      }
      strip.show();
    }

    if (I2SFlag)
    {
      if (aac->isRunning())
      {
        aac->loop();
      }
    }
  }
}