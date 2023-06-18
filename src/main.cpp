#include "audio.h"
#include "ledstrip.h"
#include "Arduino.h"
#include "vibration.h"
#include "UWB.h"

unsigned long prev_millis;

// flags
bool FSM_flag = true;

void effect_off();
void effect1();
void effect2();

void setup()
{
    Serial.begin(115200);
    led_init();
    vibro_init();
    UWB_init();
}


void loop()
{
    UWB_loop();

    // if (millis() - prev_millis >= 1)
    // {
    //     prev_millis = millis();
        
        if(state == IDLE)
        {
            effect_off();
        }

        if(state == STATE1)
        {
            effect1();
        }
        
        if(state == STATE2)
        {
            effect2();
        }
    //}
}

void effect_off()
{
    led_off();
    //vibro_off();
}

void effect1()
{
    led_rainbow();
    vibro_set(10);
}

void effect2()
{
    led_color(255, 0, 0);
}