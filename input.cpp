#include "gtaSanAndreas.h"
#include <windows.h>

void GTASanAndreas::processInput()
{
  

    // Constantes
    const char TILE_TOLL = 'T';       
    const char TILE_WALL = 'X';   
    const char TILE_EMPTY = ' ';      
    const int INTERACTION_RANGE = 1;  

    // Si el jugador no esta controlando el coche
    if (controlledCar == nullptr)
    {
        //segun que tecla presione
        Position newPlayerPosition = player.position;
        if (GetAsyncKeyState('W'))
        {
            newPlayerPosition.y--;
        }
        if (GetAsyncKeyState('S'))
        {
            newPlayerPosition.y++;
        }
        if (GetAsyncKeyState('A'))
        {
            newPlayerPosition.x--;
        }
        if (GetAsyncKeyState('D'))
        {
            newPlayerPosition.x++;
        }

        // Verificar si la nueva Posición del Player no se va del mapa
        if (newPlayerPosition.x >= 0 && newPlayerPosition.x < config.width && newPlayerPosition.y >= 0 && newPlayerPosition.y < config.height)
        {
            char tileAtNewPosition = map[newPlayerPosition.y][newPlayerPosition.x];

            // Si es un peaje
            if (tileAtNewPosition == TILE_TOLL)
            {
                // Determinar si es el peaje de San Fierro o Las Venturas
                bool isSanFierro = (newPlayerPosition.x == islandWidth);

                int tollPrice;
                if (isSanFierro)
                {
                    tollPrice = config.sanFierroToll;
                }
                else
                {
                    tollPrice = config.lasVenturasToll;
                }


                // Si el peaje ya fue pagado o el jugador tiene suficiente dinero
                if (tollPrice == 0 || player.money >= tollPrice)
                {
                    if (tollPrice > 0)
                    {
                        player.money -= tollPrice; 
                        tollPrice = 0;             

                        
                        int centerY = config.height / 2;
                        for (int i = centerY - 1; i <= centerY + 1; ++i)
                        {
                            map[i][newPlayerPosition.x] = TILE_EMPTY;
                        }

                        
                        if (isSanFierro)
                        {
                            config.sanFierroToll = 0;
                        }
                        else
                        {
                            config.lasVenturasToll = 0;
                        }
                    }

                    player.position = newPlayerPosition;
                }
            }
            // Si no es un muro, permitir el movimiento normal
            else if (tileAtNewPosition != TILE_WALL)
            {
                player.position = newPlayerPosition;
            }
        }


       
        if (GetAsyncKeyState('W'))
        {
            player.direction = '^';
        }
        if (GetAsyncKeyState('S'))
        {
            player.direction = 'v';
        }
        if (GetAsyncKeyState('A'))

        {
            player.direction = '<';
        }
        if (GetAsyncKeyState('D'))
        {
            player.direction = '>';
        }
    }
    //si el player esta controlando el coche
    else 
    {
        //Teclas para el coche
        Position newCarPosition = controlledCar->position;
        if (GetAsyncKeyState('W'))
        {
            newCarPosition.y--;
        }
        if (GetAsyncKeyState('S'))
        {
            newCarPosition.y++;
        }
        if (GetAsyncKeyState('A'))
        {
            newCarPosition.x--;
        }
        if (GetAsyncKeyState('D'))
        {
            newCarPosition.x++;
        }

        //Que el coche no se salga del mapa
        if (newCarPosition.x >= 0 && newCarPosition.x < config.width && newCarPosition.y >= 0 && newCarPosition.y < config.height)
        {
            
            char tileAtNewPosition = map[newCarPosition.y][newCarPosition.x];

            // Mover el coche si no hay muro ni peaje en la nueva casilla
            if (tileAtNewPosition != TILE_WALL && tileAtNewPosition != TILE_TOLL)
            {
                controlledCar->position = newCarPosition;
            }
        }
    }

    //Si el player le da a la tecla E para ir al coche
    if (GetAsyncKeyState(CAR_ENTER_KEY))
    {
        
        if (controlledCar == nullptr)
        {
            // Buscar coche cercano
            Car* nearbyCar = carSystem.findNearestCar(player.position.x, player.position.y);

            // Si hay un coche dentro del Rango se podra controlar
            if (nearbyCar && abs(nearbyCar->position.x - player.position.x) <= INTERACTION_RANGE &&abs(nearbyCar->position.y - player.position.y) <= INTERACTION_RANGE)
            {
                controlledCar = nearbyCar;            
                controlledCar->isControlled = true;      
                map[nearbyCar->position.y][nearbyCar->position.x] = TILE_EMPTY; 
            }
        }
        //si el player ya esta en uno
        else 
        {
            controlledCar->isControlled = false;          
            player.position = controlledCar->position;     
            controlledCar = nullptr;                       
        }
    }
}
