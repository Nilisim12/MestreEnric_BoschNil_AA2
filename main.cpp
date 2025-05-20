#include "gtaSanAndreas.h"
#include <windows.h>
#include <stdlib.h>
#include<time.h>
GTASanAndreas::GTASanAndreas() :
    FPS(10),
    map(nullptr),
    pedestrians(nullptr),
    pedestriansCount(0),
    money(nullptr),
    controlledCar(nullptr),
    viewWidth(40),
    viewHeight(20)
{
    srand(time(NULL));
    loadConfig();
    initializeMap();
    initializePlayer();
    initializePedestrians();
    carSystem.init(config.width, config.height, 5);
    showView();

    while (true)
    {
        processInput();
        update();
        Sleep(1000 / FPS);
    }
}

GTASanAndreas::~GTASanAndreas()
{
    
    Money* current = money;
    while (current != nullptr)
    {
        Money* next = current->next;
        delete current;
        current = next;
    }

    // Clear map
    if (map != nullptr)
    {
        for (int i = 0; i < config.height; i++)
        {
            delete[] map[i];
        }
        delete[] map;
    }

    delete[] pedestrians;
}

void GTASanAndreas::addMoney(Position pos, int amount)
{
    Money* newMoney = new Money;
    newMoney->position = pos;
    newMoney->amount = amount;
    newMoney->next = money;
    money = newMoney;
}

void GTASanAndreas::update()
{
    
    for (int i = 0; i < config.height; i++)
    {
        for (int j = 0; j < config.width; j++) 
        {
            if (map[i][j] != 'X') 
            { 
                map[i][j] = ' ';
            }
        }
    }

   
    if (controlledCar != nullptr) 
    {
        for (int i = 0; i < pedestriansCount; i++)
        {
            if (pedestrians[i].alive && controlledCar->pos.x == pedestrians[i].position.x &&controlledCar->pos.y == pedestrians[i].position.y)
            {

                
                pedestrians[i].alive = false;

                
                int moneyAmount = (pedestrians[i].position.x < islandWidth) ?rand() % config.losSantosMaxMoney + 1 :rand() % config.sanFierroMaxMoney + 1;

                
                Position dropPos;
                bool foundSpot = false;

                
                for (int dx = -1; dx <= 1 && !foundSpot; dx++)
                {
                    for (int dy = -1; dy <= 1 && !foundSpot; dy++)
                    {
                        if (dx == 0 && dy == 0)
                        {
                            continue;
                        }

                        int checkX = pedestrians[i].position.x + dx;
                        int checkY = pedestrians[i].position.y + dy;

                        if (checkX >= 0 && checkX < config.width &&checkY >= 0 && checkY < config.height && map[checkY][checkX] == ' ') 
                        {

                            dropPos.x = checkX;
                            dropPos.y = checkY;
                            foundSpot = true;
                        }
                    }
                }

                if (foundSpot) 
                {
                    addMoney(dropPos, moneyAmount);
                }

                regeneratePedestrian(i);
            }
        }
    }

   
    movePedestrians();
    carSystem.updateMap(map);
    if (controlledCar == nullptr) 
    {
        map[player.position.y][player.position.x] = player.direction;
    }

    if (controlledCar == nullptr) 
    {
        collectMoney();
    }
    playerAttack();
    showView();
}
int main()
{
    GTASanAndreas game;
}