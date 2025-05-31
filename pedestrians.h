#pragma once

#include "position.h"

class Pedestrian
{
public:
    Position position;
    char direction;
    bool alive;
    int life;               
    bool isAggressive;      
    int attackPower;        
    float attackCooldown;   
};
