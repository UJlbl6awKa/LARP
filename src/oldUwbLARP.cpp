#include "oldUwbLARP.h"
#include "LARP.h"

// connection pins
uint8_t PIN_RST = 27; // reset pin
uint8_t PIN_IRQ = 34; // irq pin
uint8_t PIN_SS = 4;   // spi select pin

typedef enum
{
  HEAL,
  DAMAGED,
  DEAD,
} HERO_STATE;

HERO_STATE current_state;

byte tag_addr[8] = {0x7D, 0x00, 0x22, 0xEA, 0x82, 0x60, 0x3B, 0x9C};
byte damage_addr[8] = {0x82, 0x17, 0x5B, 0xD5, 0xA9, 0x9A, 0xE2, 0x9C};
byte heal_addr[8] = {0x82, 0x17, 0x5B, 0xD5, 0xA9, 0x9A, 0x00, 0x00};

void old_uwb_init(bool type)
{
  // init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); // Reset, CS, IRQ pin
  // define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  // Enable the filter to smooth the distance
  DW1000Ranging.useRangeFilter(true);

  if (type == 0)
  // we start the module as a tag
  {
    DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
  }
  else
  // we start the module as an anchor
  {
    DW1000Ranging.startAsAnchor("82:17:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
  }
}

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

  if {DW1000Ranging.getDistantDevice()->getRange() && }
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