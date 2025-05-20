#pragma once
#include <windows.h>
#include "config.h"
#include "player.h"
#include "position.h"
#include "pedestrians.h"
#include "money.h"
#include "Cars.h"

const int ATTACK_KEY = VK_SPACE;
const int CAR_ENTER_KEY = 'E';

class GTASanAndreas
{
public:
    GTASanAndreas();
    ~GTASanAndreas();

private:
    Config config;
    char** map;
    Player player;
    int islandWidth;
    Pedestrian* pedestrians;
    int pedestriansCount;
    int viewWidth;
    int viewHeight;
    int FPS;
    Money* money;
    Car* controlledCar;
    CarSystem carSystem;

    void loadConfig();
    void initializeMap();
    void initializePlayer();
    void initializePedestrians();
    void regeneratePedestrian(int index);
    bool isNextToPlayer(const Position& pedestrianPos);
    void movePedestrians();
    void addMoney(Position pos, int amount);
    void playerAttack();
    void collectMoney();
    void processInput();
    void showView();
    void update();
};

