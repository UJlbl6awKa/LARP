#pragma once

#define LED_NUM 9
#define STRIP_PIN 15

// конфигурация ленты
void led_init();

// выключить все светодиоды                             
void led_off();                

// зажечь все светодиоды на выбранную яркость                     
void led_color(int color1, int color2, int color3);    

// зажечь радугу
void led_rainbow();        

// зажечь бегущую радугу                         
void led_running_rainbow();               

// мигание c заданной частотой                
void led_blinking(int color1, int color2, int color3, int speed);                      