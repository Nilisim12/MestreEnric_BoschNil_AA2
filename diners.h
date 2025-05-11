#pragma once
#ifndef DINERS_H
#define DINERS_H

#include "posicio.h"

struct Diners
{
    Posicio posicio;
    int cantitat;
    Diners* diners;
};

#endif