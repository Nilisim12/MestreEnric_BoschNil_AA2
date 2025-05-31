#include "gtaSanAndreas.h"
#include <windows.h>

void GTASanAndreas::initializePlayer()
{
   //Inicializar Person
    player.position.x = config.width / 6;  
    player.position.y = config.height / 2;  
    player.previousPosition = player.position;
    player.direction = '^';                  
    player.money = 0;                    
    player.life = config.cjLife;              
    player.attackPower = config.cjAttack;  
}

void GTASanAndreas::playerAttack()
{
   //si le ha dado a la tecla Espacio
    if (GetAsyncKeyState(ATTACK_KEY))
    {
        
        for (int i = 0; i < pedestriansCount; i++)
        {
            
            if (!pedestrians[i].alive)
            {
                continue;  
            }
            //Calcular la distancia de 1 de x y respecto al jugador
            
            if (abs(player.position.x - pedestrians[i].position.x) <= 1 && abs(player.position.y - pedestrians[i].position.y) <= 1)
            {
                
                pedestrians[i].life -= player.attackPower;

                //Peaton muerto
                if (pedestrians[i].life <= 0)
                {
                    pedestrians[i].alive = false;                  
                    map[pedestrians[i].position.y][pedestrians[i].position.x] = ' '; 

                    int moneyAmount;

                    
                    if (pedestrians[i].position.x < islandWidth)
                    {
                        moneyAmount = rand() % config.losSantosMaxMoney + 1;
                    }
                    else
                    {
                        moneyAmount = rand() % config.sanFierroMaxMoney + 1;
                    }

                 
                    addMoney(pedestrians[i].position, moneyAmount);

                    
                    regeneratePedestrian(i);
                }

               //si peaton es agresivo que ataque con cooldown 1s
                if (pedestrians[i].isAggressive && pedestrians[i].attackCooldown <= 0)
                {
                    player.life -= pedestrians[i].attackPower;    
                    pedestrians[i].attackCooldown = 1.0f;         
                }
            }
        }
    }
}

void GTASanAndreas::collectMoney()
{
    Money* current = money;      
    Money* previous = nullptr;     

   //recoger dinero si esta en la misma posicion que Player
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
