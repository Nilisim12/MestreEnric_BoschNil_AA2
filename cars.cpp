#include "Cars.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>

CarSystem::CarSystem() : carsArray(nullptr), capacity(0), count(0)
{


}

CarSystem::~CarSystem()
{
    clearAll();
}

void CarSystem::init(int mapWidth, int mapHeight, int numCars)
{
    clearAll();
    capacity = numCars;
    count = numCars;
    carsArray = new Car[capacity];

    for (int i = 0; i < count; ++i)
    {
        carsArray[i].pos.x = 5 + rand() % (mapWidth - 10);
        carsArray[i].pos.y = 5 + rand() % (mapHeight - 10);
        carsArray[i].controlled = false;
    }
}

void CarSystem::updateMap(char** map) 
{
    for (int i = 0; i < count; i++) 
    {
        if (!carsArray[i].controlled && map[carsArray[i].pos.y][carsArray[i].pos.x] != 'X' &map[carsArray[i].pos.y][carsArray[i].pos.x] != 'C') 
        { 
            map[carsArray[i].pos.y][carsArray[i].pos.x] = 'C';
        }
    }
}

Car* CarSystem::getCarAt(int x, int y)
{
    for (int i = 0; i < count; i++) 
    {
        if (carsArray[i].pos.x == x && carsArray[i].pos.y == y)
        {
            return &carsArray[i];
        }
    }
    return nullptr;
}

Car* CarSystem::getNearestCar(int x, int y)
{
    if (count == 0) return nullptr;

    Car* nearest = nullptr;
    int minDist = 2;

    for (int i = 0; i < count; i++)
    {
        int currentDist = abs(carsArray[i].pos.x - x) + abs(carsArray[i].pos.y - y);

        
        if (currentDist <= 1 && currentDist < minDist)
        {
            minDist = currentDist;
            nearest = &carsArray[i];
        }
    }

    return nearest; 
}

bool CarSystem::isCarNear(int x, int y, int range)
{
    for (int i = 0; i < count; i++)
    {
        if (abs(carsArray[i].pos.x - x) <= range && abs(carsArray[i].pos.y - y) <= range)
        {
            return true;
        }
    }
    return false;
}

void CarSystem::clearAll()
{
    delete[] carsArray;
    carsArray = nullptr;
    capacity = 0;
    count = 0;
}
