#pragma once
#ifndef JUGADOR_H
#define JUGADOR_H

#include "posicio.h"

struct Jugador
{
    Posicio posicio;
    Posicio posAnterior;
    char Direccio;
    int diners;
};

#endif