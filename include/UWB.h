/***********\ DW 1000 header file /***********/
#include <SPI.h>
#include <DW1000Ranging.h>

// connection pins
const uint8_t PIN_RST = 27; // reset pin
const uint8_t PIN_IRQ = 34; // irq pin
const uint8_t PIN_SS = 4;   // spi select pin

void uwbSetup();
void newRange();
void newDevice(DW1000Device *device);
void inactiveDevice(DW1000Device *device);