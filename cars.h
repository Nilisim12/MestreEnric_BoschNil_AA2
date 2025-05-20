#pragma once
#include "position.h"

class Car
{
public:

    Position pos;
    bool controlled;
    void move(int dx, int dy)
    {
        pos.x += dx;
        pos.y += dy;
    }
};

class CarSystem
{
private:
    Car* carsArray;
    int capacity;
    int count;


public:
    CarSystem();
    ~CarSystem();

    void init(int mapWidth, int mapHeight, int numCars);
    void updateMap(char** map);
    Car* getCarAt(int x, int y);
    Car* getNearestCar(int x, int y);
    bool isCarNear(int x, int y, int range = 1);
    void clearAll();
};
