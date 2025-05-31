#include "gtaSanAndreas.h"
#include <iostream>

void GTASanAndreas::showView()
{
    system("cls");  

    std::cout << "                 GTA SAN ANDREAS" << std::endl;

    
    map[player.previousPosition.y][player.previousPosition.x] = ' ';

    //dibuja el dinero
    Money* Money = money;
    while (Money != nullptr)
    {
        map[Money->position.y][Money->position.x] = '$';
        Money = Money->next;
    }

    //dibuja los coches
    carSystem.drawCarsOnMap(map);

    //dibuja el coche
    if (controlledCar != nullptr)
    {
        map[controlledCar->position.y][controlledCar->position.x] = 'C';
    }
    else
    {
       
        map[player.position.y][player.position.x] = player.direction;
    }


    int viewX = player.position.x - viewWidth / 2;
    int viewY = player.position.y - viewHeight / 2;

    
    if (viewX < 0)
    {
        viewX = 0;
    }
    if (viewX > config.width - viewWidth)
    {
        viewX = config.width - viewWidth;
    }
    if (viewY < 0)
    {
        viewY = 0;
    }
    if (viewY > config.height - viewHeight)
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

   
    std::cout << "\nCJ Health: [";
    int currentLife;
    if (player.life < 0)
    {
        currentLife = 0;
    }
    else
    {
        currentLife = player.life;
    }

    int maxLife;
    if (config.cjLife <= 0)
    {
        maxLife = 1;
    }
    else
    {
        maxLife = config.cjLife;
    }

    float lifeRatio = static_cast<float>(currentLife) / maxLife;   
    int lifeBars = static_cast<int>(20 * lifeRatio);               

    
    if (lifeBars < 0)
    {
        lifeBars = 0;
    }
    if (lifeBars > 20)
    {
        lifeBars = 20;
    }

    //vida Personaje
    for (int i = 0; i < 20; i++)
    {
        if (i < lifeBars) 
        {
            std::cout << '#';
        }
        else
        {
            std::cout << '-';
        }
    }

    
    std::cout << "] " << currentLife << "/" << maxLife;
    std::cout << " | Money: $" << player.money;
    std::cout << " | Money to SAN FRANCISCO: $" << config.sanFierroToll;
    std::cout << " | Money to  LV: $" << config.lasVenturasToll << std::endl;

    //si el jugador esta en un coche
    if (controlledCar != nullptr)
    {
        std::cout << "In car (WASD to move, E to exit)" << std::endl;
    }


    if (controlledCar == nullptr)
    {
        map[player.position.y][player.position.x] = ' ';
    }
}
