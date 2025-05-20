#include "gtaSanAndreas.h"
#include <iostream>

void GTASanAndreas::showView()
{
    system("cls");
    std::cout << "                 GTA SAN ANDREAS" << std::endl;

    
    map[player.previousPosition.y][player.previousPosition.x] = ' ';

   
    Money* temp = money;
    while (temp != nullptr)
    {
        map[temp->position.y][temp->position.x] = '$';
        temp = temp->next;
    }

  
    carSystem.updateMap(map);

    
    if (controlledCar != nullptr)
    {
        map[controlledCar->pos.y][controlledCar->pos.x] = 'C';
    }
    else
    {
        char original = map[player.position.y][player.position.x];
        map[player.position.y][player.position.x] = player.direction;
    }

    
    int viewX = player.position.x - viewWidth / 2;
    int viewY = player.position.y - viewHeight / 2;

    if (viewX < 0)
    {
        viewX = 0;
    }
    if (viewY < 0)
    {
        viewY = 0;
    }
    if (viewX + viewWidth > config.width)
    {
        viewX = config.width - viewWidth;
    }
    if (viewY + viewHeight > config.height)
    {
        viewY = config.height - viewHeight;
    }

    
    for (int i = viewY; i < viewY + viewHeight && i < config.height; i++)
    {
        for (int j = viewX; j < viewX + viewWidth && j < config.width; j++)
        {
            std::cout << map[i][j];
        }
        std::cout << '\n';
    }

    
    if (controlledCar == nullptr)
    {
        map[player.position.y][player.position.x] = ' ';
    }

    std::cout << "Money: " << player.money << std::endl;
    if (controlledCar != nullptr)
    {
        std::cout << "In car (WASD to move, E to exit)" << std::endl;
    }
}