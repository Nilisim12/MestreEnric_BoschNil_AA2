#pragma once
#include "position.h"

class Car
{
public:
    Position position;      
    bool isControlled;      

    void move(int newX, int newY)
    {
        position.x += newX;
        position.y += newY;
    }
};

class CarSystem
{
private:
    Car* carList;         
    int totalCapacity;      
    int activeCarCount;  

public:
    CarSystem();
    ~CarSystem();

    void initializeCars(int mapWidth, int mapHeight, int numberOfCars);  
    void drawCarsOnMap(char** map);                                      
    Car* findCarAtPosition(int x, int y);                               
    Car* findNearestCar(int x, int y);                                
    bool isCarNear(int x, int y, int range = 1);                 
    void removeAllCars();                                      
};
