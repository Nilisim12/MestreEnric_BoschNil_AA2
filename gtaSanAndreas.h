#pragma once
<<<<<<< HEAD
#ifndef GTA_SAN_ANDREAS_H
#define GTA_SAN_ANDREAS_H

#include <windows.h>
#include "config.h"
#include "jugador.h"
#include "peatons.h"
#include "diners.h"

#define ATTACK_KEY VK_SPACE

class GTASANANDREAS
{
public:
    GTASANANDREAS();
    ~GTASANANDREAS();

private:
    Config config;
    char** mapa;
    Jugador jugador;
    int ampladaIsla;
    Peatons* peatons;
    int cantitatPeatons;
    int ampladaVista;
    int alturaVista;
    int FPS;
    Diners* diners;

    void cargarConfiguracio();
    void inicialitzarMapa();
    void inicialitzarJugador();
    void inicialitzarPeatons();
    void regenerarPeaton(int indice);
    bool estaCostatJugador(const Posicio& posPeaton);
    void mourePeatons();
    void agregarDiners(Posicio pos, int cantidad);
    void AtacJugador();
    void recollirDiners();
    void procesarInput();
    void mostrarVista();
    void actualizar();
};

#endif
=======
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
    void updatePedestrians();

};
>>>>>>> Peaton
