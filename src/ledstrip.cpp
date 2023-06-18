#include "ledstrip.h"
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel strip(LED_NUM, STRIP_PIN); // количество светодиодов и пин

unsigned long last_time;

// настройка светодиодной ленты
void led_init()
{
    strip.begin();
}

void led_off()
{
    for (uint8_t i; i <= strip.numPixels(); i++)
    {
        strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
}

void led_green()
{
    for (uint8_t i; i <= strip.numPixels(); i++)
    {
        strip.setPixelColor(i, 0, 128, 0);
    }
    strip.show();
}

void led_color(int red, int green, int blue)
{
    for (byte i; i <= strip.numPixels(); i++)
    {
        strip.setPixelColor(i, red, green, blue);
    }
    strip.show();
}

void led_rainbow()
{
    strip.rainbow();
    strip.show();
}

void led_running_rainbow()
{
    for (uint8_t i = 0; i < 65535; i += 100)
    {
        strip.rainbow(i, 1, 255, 128);
        strip.show();
    }
}

void led_blinking(int red, int green, int blue, int speed)
{
    if (millis() - last_time >= speed)
    {
        last_time = millis();
        led_color(red, green, blue);
    }
    else
    {
        led_off();
    }
}
