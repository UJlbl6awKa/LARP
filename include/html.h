/***********\ HTML header file /***********/
#pragma once

#define LED_BUILTIN 2
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

WebServer server(80);

const char *ssid = "Кукушка";
const char *password = "RVSNRMTO";
char htmlResponse[3000];

void htmlStart();   
void handleRoot();
void handleSave();