#include "Cars.h"
#include <algorithm>
#include <math.h>   
#include <stdlib.h>

//constantes
const int carMargin = 5;
const int minDistCar = 2;
const int maxDistCar = 1;

CarSystem::CarSystem() : carList(nullptr), totalCapacity(0), activeCarCount(0)
{
}

CarSystem::~CarSystem()
{
    removeAllCars();
}
//inicializar los coches
void CarSystem::initializeCars(int mapWidth, int mapHeight, int numCars)
{
    removeAllCars();
    totalCapacity = numCars;
    activeCarCount = numCars;
    carList = new Car[totalCapacity];
    //inicializar los coches en posiciones aleatorias
    for (int i = 0; i < activeCarCount; ++i)
    {
        carList[i].position.x = carMargin + rand() % (mapWidth - 2 * carMargin);
        carList[i].position.y = carMargin + rand() % (mapHeight - 2 * carMargin);
        carList[i].isControlled = false;
    }
}

void CarSystem::drawCarsOnMap(char** map)
{
    for (int i = 0; i < activeCarCount; i++)
    {
       
        //dibujar el coche en el mapa y que no este en la misma posicion que X,
        if (!carList[i].isControlled && map[carList[i].position.y][carList[i].position.x] != 'X' && map[carList[i].position.y][carList[i].position.x] != 'C')
        {
            map[carList[i].position.y][carList[i].position.x] = 'C';
        }
    }
}
//si se encuentra un coche en la posicion x y que haga return del coche sino nullptr
Car* CarSystem::findCarAtPosition(int x, int y)
{
    for (int i = 0; i < activeCarCount; i++)
    {
        if (carList[i].position.x == x && carList[i].position.y == y)
        {
            return &carList[i];
        }
    }
    return nullptr;
}
//Encontrar un coche que este al lado del player
Car* CarSystem::findNearestCar(int x, int y)
{
    if (activeCarCount == 0)
    {
        return nullptr;
    }

    Car* nearest = nullptr;
    int minDist = minDistCar;

    for (int i = 0; i < activeCarCount; i++)
    {
        //Calcula la distancia para saber si el player y coche estan al lado
        int currentDist = abs(carList[i].position.x - x) + abs(carList[i].position.y - y);

        if (currentDist <= maxDistCar && currentDist < minDist)
        {
            minDist = currentDist;
            nearest = &carList[i];
        }
    }

    return nearest;
}

bool CarSystem::isCarNear(int x, int y, int range)
{
    for (int i = 0; i < activeCarCount; i++)
    {
        //retorna true si es menor o igual al range
        if (abs(carList[i].position.x - x) <= range && abs(carList[i].position.y - y) <= range)
        {
            return true;
        }
    }
    return false;
}
//Eliminar los coches manualmente
void CarSystem::removeAllCars()
{
    delete[] carList;
    carList = nullptr;
    totalCapacity = 0;
    activeCarCount = 0;
}
