#include "gtaSanAndreas.h"

void GTASanAndreas::initializePedestrians()
{
    pedestriansCount = config.losSantosPedestrians + config.sanFierroPedestrians;
    pedestrians = new Pedestrian[pedestriansCount];

   
    for (int i = 0; i < config.losSantosPedestrians; i++)
    {
        pedestrians[i].position.x = 5 + rand() % (islandWidth - 10);
        pedestrians[i].position.y = 5 + rand() % (config.height - 10);
        pedestrians[i].direction = (rand() % 2 == 0) ? 'H' : 'V';
        pedestrians[i].alive = true;
        map[pedestrians[i].position.y][pedestrians[i].position.x] = 'P';
    }

    
    for (int i = 0; i < config.sanFierroPedestrians; i++)
    {
        int index = config.losSantosPedestrians + i;
        pedestrians[index].position.x = islandWidth + 5 + rand() % (islandWidth - 10);
        pedestrians[index].position.y = 5 + rand() % (config.height - 10);
        pedestrians[index].direction = (rand() % 2 == 0) ? 'H' : 'V';
        pedestrians[index].alive = true;
        map[pedestrians[index].position.y][pedestrians[index].position.x] = 'P';
    }
}

void GTASanAndreas::regeneratePedestrian(int index)
{
    if (pedestrians[index].position.x < islandWidth)
    {
        pedestrians[index].position.x = 5 + rand() % (islandWidth - 10);
    }
    else
    {
        pedestrians[index].position.x = islandWidth + 5 + rand() % (islandWidth - 10);
    }
    pedestrians[index].position.y = 5 + rand() % (config.height - 10);
    pedestrians[index].alive = true;
    map[pedestrians[index].position.y][pedestrians[index].position.x] = 'P';
}

bool GTASanAndreas::isNextToPlayer(const Position& pedestrianPos)
{
    return (abs(player.position.x - pedestrianPos.x) <= 1 &&
        abs(player.position.y - pedestrianPos.y) <= 1);
}

void GTASanAndreas::movePedestrians()
{
    for (int i = 0; i < pedestriansCount; i++)
    {
        if (!pedestrians[i].alive)
        {
            continue;
        }

       
        if (!isNextToPlayer(pedestrians[i].position))
        {
            map[pedestrians[i].position.y][pedestrians[i].position.x] = ' ';

            if (pedestrians[i].direction == 'H')
            {
                int newX = pedestrians[i].position.x + (rand() % 3 - 1);
                if (newX > 0 && newX < config.width - 1 && map[pedestrians[i].position.y][newX] == ' ')
                {
                    pedestrians[i].position.x = newX;
                }
            }
            else
            {
                int newY = pedestrians[i].position.y + (rand() % 3 - 1);
                if (newY > 0 && newY < config.height - 1 && map[newY][pedestrians[i].position.x] == ' ')
                {
                    pedestrians[i].position.y = newY;
                }
            }
        }

      
        map[pedestrians[i].position.y][pedestrians[i].position.x] = 'P';
    }
}