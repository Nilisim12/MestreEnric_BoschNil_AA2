#pragma once
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