#include "gtaSanAndreas.h"
#include <windows.h>

void GTASanAndreas::processInput()
{
    player.previousPosition = player.position;

    if (GetAsyncKeyState('W') && player.position.y > 1 && map[player.position.y - 1][player.position.x] != 'X')
    {
        player.position.y--;
        player.direction = '^';
    }
    else if (GetAsyncKeyState('S') && player.position.y < config.height - 2 && map[player.position.y + 1][player.position.x] != 'X')
    {
        player.position.y++;
        player.direction = 'v';
    }
    else if (GetAsyncKeyState('A') && player.position.x > 1 && map[player.position.y][player.position.x - 1] != 'X')
    {
        player.position.x--;
        player.direction = '<';
    }
    else if (GetAsyncKeyState('D') && player.position.x < config.width - 2 && map[player.position.y][player.position.x + 1] != 'X')
    {
        player.position.x++;
        player.direction = '>';
    }
    else if (GetAsyncKeyState(CAR_ENTER_KEY))
    {
        if (controlledCar == nullptr) 
        {
            
            Car* car = carSystem.getNearestCar(player.position.x, player.position.y);
            if (car != nullptr) 
            {
                controlledCar = car;
                controlledCar->controlled = true;
            }
        }
        else 
        {
          
            controlledCar->controlled = false;
            map[controlledCar->pos.y][controlledCar->pos.x] = 'C';
            player.position = controlledCar->pos; 
            controlledCar = nullptr;
        }
    
    }

    if (controlledCar != nullptr) 
    {
        
        map[controlledCar->pos.y][controlledCar->pos.x] = ' ';

        Position newPos = controlledCar->pos;

        if (GetAsyncKeyState('W')) newPos.y--;
        else if (GetAsyncKeyState('S')) newPos.y++;
        else if (GetAsyncKeyState('A')) newPos.x--;
        else if (GetAsyncKeyState('D')) newPos.x++;

        
        if (newPos.x >= 0 && newPos.x < config.width &&
            newPos.y >= 0 && newPos.y < config.height &&
            map[newPos.y][newPos.x] != 'X') {
            controlledCar->pos = newPos;
        }

      
        map[controlledCar->pos.y][controlledCar->pos.x] = 'C';
    }
}