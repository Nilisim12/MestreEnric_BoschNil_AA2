#include "gtaSanAndreas.h"

void GTASanAndreas::initializeMap()
{
    map = new char* [config.height];

    for (int i = 0; i < config.height; i++)
    {
        map[i] = new char[config.width];
        for (int j = 0; j < config.width; j++)
        {
            map[i][j] = ' ';
        }
    }

    islandWidth = config.width / 3;

   
    for (int i = 0; i < config.height; i++)
    {
        map[i][islandWidth] = 'X';
        map[i][islandWidth * 2] = 'X';

        
        if (i >= config.height / 2 - 1 && i <= config.height / 2 + 1)
        {
            if (config.sanFierroToll > 0)
            {

                map[i][islandWidth] = 'T';
            }
            if (config.lasVenturasToll > 0)
            {
                map[i][islandWidth * 2] = 'T';
            }
        }
    }


    for (int j = 0; j < config.width; j++)
    {
        map[0][j] = 'X';
        map[config.height - 1][j] = 'X';
    }
}