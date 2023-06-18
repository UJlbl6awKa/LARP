#include "UWB.h"
#include <SPI.h>
#include "DW1000.h"
#include "DW1000Ranging.h"
#include "Arduino.h"

#define DEVICE_IS_TAG

#define ANCHOR1 "01:00:22:EA:82:60:3B:9A"
#define ANCHOR2 "02:00:22:EA:82:60:3B:9B"
#define TAG1 "73:00:22:EA:82:60:3B:9C"

State state = IDLE;

// connection pins
const uint8_t PIN_RST = 27; // reset pin
const uint8_t PIN_IRQ = 34; // irq pin
const uint8_t PIN_SS = 4;   // spi select pin

void UWB_init()
{
  delay(1000);
  // init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); // Reset, CS, IRQ pin
  // define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  // Enable the filter to smooth the distance
  DW1000Ranging.useRangeFilter(true);

// we start the module as a tag
#ifdef DEVICE_IS_TAG
  DW1000Ranging.startAsTag(TAG1, DW1000.MODE_LONGDATA_RANGE_ACCURACY, false);
#endif
#ifdef DEVICE_IS_ANCHOR1
  DW1000Ranging.startAsAnchor(ANCHOR1, DW1000.MODE_LONGDATA_RANGE_ACCURACY, false);
#endif
#ifdef DEVICE_IS_ANCHOR2
  DW1000Ranging.startAsAnchor(ANCHOR2, DW1000.MODE_LONGDATA_RANGE_ACCURACY, false);
#endif
}

void UWB_loop()
{
  DW1000Ranging.loop();
}

void newRange()
{
  // Serial.print("from: ");
  // Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  // Serial.print("\t Range: ");
  // Serial.print(DW1000Ranging.getDistantDevice()->getRange());
  // Serial.print(" m");
  // Serial.print("\t RX power: ");
  // Serial.print(DW1000Ranging.getDistantDevice()->getRXPower());
  // Serial.println(" dBm\t");
  uint16_t anc1_short_adress = 1;
  uint16_t anc2_short_adress = 2;
  Serial.print(anc1_short_adress);

  if (anc1_short_adress == DW1000Ranging.getDistantDevice()->getShortAddress())
  {
    if (DW1000Ranging.getDistantDevice()->getRange() < 1.5)
    {
      if (state == IDLE)
      {
        state = STATE1;
        Serial.println("\n\n\nState Changed 1\n\n\n");
      }
    }
  }

  if (anc2_short_adress == DW1000Ranging.getDistantDevice()->getShortAddress())
  {
    if (DW1000Ranging.getDistantDevice()->getRange() < 1.5)
    {
      if (state == STATE1)
      {
        state = STATE2;
        Serial.println("\n\n\nState Changed 2\n\n\n");
      }
    }
  }
}

  void newDevice(DW1000Device * device)
  {
    Serial.print("ranging init; 1 device added ! -> ");
    Serial.print(" short:");
    Serial.println(device->getShortAddress(), HEX);
  }

  void inactiveDevice(DW1000Device * device)
  {
    Serial.print("delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
  }
