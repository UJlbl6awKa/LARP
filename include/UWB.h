/***********\ DWM 1000 /***********/
#pragma once
#include "DW1000Device.h"

enum State
{
    IDLE,
    STATE1,
    STATE2
};

extern State state;

void UWB_init();

void UWB_loop();

void newRange();

void newDevice(DW1000Device* device);

void inactiveDevice(DW1000Device* device);