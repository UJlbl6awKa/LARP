#include "vibration.h"
#include "Arduino.h"

void vibro_init()
{
    pinMode(VIBRO_PIN, OUTPUT);
}

void vibro_off()
{
    analogWrite(VIBRO_PIN, 0);
}

void vibro_set(int val)
{
    analogWrite(VIBRO_PIN, val);
}