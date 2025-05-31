#include "gtaSanAndreas.h"
<<<<<<< HEAD

int main()
{
    GTASANANDREAS juego;
    return 0;
}
=======
#include <windows.h>
#include <stdlib.h>
#include <time.h>


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
    carSystem.initializeCars(config.width, config.height, 5);
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
            if (map[i][j] != 'X' && map[i][j] != 'T')
            {
                map[i][j] = ' ';
            }
        }
    }

    // Borra el peaje si ya ha sido pagado
    for (int i = config.height / 2 - 1; i <= config.height / 2 + 1; i++)
    {
        if (config.sanFierroToll <= 0)
        {
            map[i][islandWidth] = ' ';
        }
        if (config.lasVenturasToll <= 0)
        {
            map[i][islandWidth * 2] = ' ';
        }
    }

    // Si se esta controlando un coche
    if (controlledCar != nullptr)
    {
        for (int i = 0; i < pedestriansCount; i++)
        {
            // Si el coche atropella a un peaton
            if (pedestrians[i].alive &&controlledCar->position.x == pedestrians[i].position.x && controlledCar->position.y == pedestrians[i].position.y)
            {
                pedestrians[i].alive = false;

                // Calcula la cantidad de dinero si esta en los Santos o San Fierro
                int moneyAmount;
                if (pedestrians[i].position.x < islandWidth)
                {
                    moneyAmount = rand() % config.losSantosMaxMoney + 1;
                }
                else 
                {
                    moneyAmount = rand() % config.sanFierroMaxMoney + 1;
                }


                // Posicion cercana para el dinero
                Position dropPos;
                bool foundSpot = false;
                for (int x = -1; x <= 1 && !foundSpot; x++)
                {
                    for (int y = -1; y <= 1 && !foundSpot; y++)
                    {
                        if (x == 0 && y == 0)
                        {
                            continue;
                        }

                        int checkX = pedestrians[i].position.x + x;
                        int checkY = pedestrians[i].position.y + y;

                        if (checkX >= 0 && checkX < config.width &&checkY >= 0 && checkY < config.height && map[checkY][checkX] == ' ')
                        {
                            dropPos.x = checkX;
                            dropPos.y = checkY;
                            foundSpot = true;
                        }
                    }
                }

               //si encuentra lugar que se añada y se imprima
                if (foundSpot)
                {
                    addMoney(dropPos, moneyAmount);
                }

              
                regeneratePedestrian(i);
            }
        }
    }

    
    movePedestrians();

   
    carSystem.drawCarsOnMap(map);


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
    return 0;
}
>>>>>>> Peaton
