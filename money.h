#pragma once
#include "position.h"

class Money
{
public:
    Position position;
    int amount;
    Money* next;
};