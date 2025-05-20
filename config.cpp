#include "gtaSanAndreas.h"
#include <fstream>
#include <iostream>

void GTASanAndreas::loadConfig()
{
    std::ifstream file("config.txt");
    if (file.is_open())
    {
        char separator;

        file >> config.width >> separator >> config.height >> separator;
        file >> config.cjLife >> separator >> config.cjAttack >> separator;
        file >> config.sanFierroToll >> separator >> config.lasVenturasToll >> separator;

        file >> config.losSantosPedestrians >> separator >> config.losSantosMaxMoney >> separator>> config.losSantosPedestriansLife >> separator >> config.losSantosPedestriansAttack >> separator;

        file >> config.sanFierroPedestrians >> separator >> config.sanFierroMaxMoney >> separator>> config.sanFierroPedestriansLife >> separator >> config.sanFierroPedestriansAttack >> separator;

        file >> config.lasVenturasPedestrians >> separator >> config.lasVenturasMaxMoney >> separator>> config.lasVenturasPedestriansLife >> separator >> config.lasVenturasPedestriansAttack;

        file.close();
    }
    else
    {
        std::cout << "Cannot open config file\n";
        
    }
}