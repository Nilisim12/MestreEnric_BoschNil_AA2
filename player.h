#pragma once
#include "position.h"


class Player
{
public:
    Position position;
    Position previousPosition;
    char direction;
    int money;
    int life;               
    int attackPower;        
};
