/***********\ DW 1000 /***********/
#include <SPI.h>
#include "DW1000Ranging.h"

// connection pins
const uint8_t PIN_RST = 27; // reset pin
const uint8_t PIN_IRQ = 34; // irq pin
const uint8_t PIN_SS = 4;   // spi select pin

/***********\ LED Strip /***********/
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel strip(17, 15); // количество светодиодов и пин
/***********\ HTML /***********/
#define LED_BUILTIN 2
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
WebServer server(80);

const char *ssid = "onlime_8";
const char *password = "9060547016";
char htmlResponse[3000];

/***********\ I2S AUDIO /***********/
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

//millis
unsigned long prev_millis = 0;

// флаги
bool ledFlag = false;
bool I2SFlag = false;

/******************************************************/
//                       ФУНКЦИИ
/******************************************************/

// для работы с HTML

void handleRoot() {
  snprintf ( htmlResponse, 3000,
  "<!DOCTYPE html>\
  <html lang=\"en\">\
    <head>\
      <meta charset=\"utf-8\">\
      <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
    </head>\
    <body>\
      <h1>LED</h1>\
      <div>\
      <button id=\"led_button_on\">Turn on LED</button><button id=\"led_button_off\">Turn off LED</button>\
      </div>\   
      <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>\    
      <script>\
        $('#led_button_off').click(function(e){\
          e.preventDefault();\
          var led=1;\
          $.get('/save?led=' + led, function(data){\
            console.log(data);\
          });\
        });\   
        $('#led_button_on').click(function(e){\
          e.preventDefault();\
          var led=2;\
          $.get('/save?led=' + led, function(data){\
            console.log(data);\
          });\
        });\  
      </script>\
    </body>\
  </html>"); 
  server.send ( 200, "text/html", htmlResponse );  
  Serial.println("HANDLING ROOT");
}
void handleSave() // переделать
{
  // Serial.println(server.args());
  if (server.args() == 1)
  {
    if (server.arg("led").toInt() == 1)
    {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("Changing LED state to OFF");
    }
    else
    {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Changing LED state to ON");
    }
  }
}

// UWB

void newRange()
{
  Serial.print("from: ");
  Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  Serial.print("\t Range: ");
  Serial.print(DW1000Ranging.getDistantDevice()->getRange());
  Serial.print(" m");
  Serial.print("\t RX power: ");
  Serial.print(DW1000Ranging.getDistantDevice()->getRXPower());
  Serial.println(" dBm");
}

void newDevice(DW1000Device *device)
{
  Serial.print("ranging init; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device *device)
{
  Serial.print("delete inactive device: ");
  Serial.println(device->getShortAddress(), HEX);
}

/*
void ledEffect()
{

}
*/

/******************************************************/
//                     ПУПА и ЛУПА
/******************************************************/

void setup()
{
  Serial.begin(115200); // UART
  delay(1000);

  /* настройка светодиодки*/
  strip.begin()
  /* настройка DW1000*/
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); // Reset, CS, IRQ pin
  // define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  // Enable the filter to smooth the distance
  DW1000Ranging.useRangeFilter(true);
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY); // we start the module as a tag

  /* настройка DW1000*/
  audioLogger = &Serial;
  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();
  out->SetGain(GAIN);
  out->SetPinout(Bit_Clock_BCLK, Word_Select_WS, Serial_Data_SD);
  aac->begin(in, out);
}

void loop()
{ /*
  // опрос датчика
  if (millis() - prev_millis >= 10)
  {
    prev_millis = millis();

    DW1000Ranging.loop();
    handleRoot();
  }

  if (DW1000Ranging.getDistantDevice()->getRange() <= 0.5)
  {
    ledFlag = true;
  }

  if (ledFlag = true)
  {
  }
  else
  {
  }

  if (I2SFlag = true)
  {
    if (aac->isRunning())
    {
      aac->loop();
    }
  }*/
}

