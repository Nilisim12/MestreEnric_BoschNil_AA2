#include "gtaSanAndreas.h"
#include <windows.h>

void GTASanAndreas::initializePlayer()
{
    player.position.x = config.width / 2;
    player.position.y = config.height / 2;
    player.previousPosition = player.position;
    player.direction = '^';
    player.money = 0;
}

void GTASanAndreas::playerAttack()
{
    if (GetAsyncKeyState(ATTACK_KEY))
    {
        for (int i = 0; i < pedestriansCount; i++)
        {
            if (!pedestrians[i].alive)
            {
                continue;
            }

            if (abs(player.position.x - pedestrians[i].position.x) <= 1 && abs(player.position.y - pedestrians[i].position.y) <= 1)
            {
                pedestrians[i].alive = false;
                map[pedestrians[i].position.y][pedestrians[i].position.x] = ' ';

                int moneyAmount = (pedestrians[i].position.x < islandWidth) ?
                    rand() % config.losSantosMaxMoney + 1 :
                    rand() % config.sanFierroMaxMoney + 1;

                addMoney(pedestrians[i].position, moneyAmount);
                regeneratePedestrian(i);
            }
        }
    }
}

void GTASanAndreas::collectMoney()
{
    Money* current = money;
    Money* previous = nullptr;

    while (current != nullptr)
    {
        if (player.position.x == current->position.x && player.position.y == current->position.y)
        {
            player.money += current->amount;

            if (previous == nullptr)
            {
                money = current->next;
                delete current;
                current = money;
            }
            else
            {
                previous->next = current->next;
                delete current;
                current = previous->next;
            }
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}