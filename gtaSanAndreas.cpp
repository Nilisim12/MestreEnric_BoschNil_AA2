#include "gtaSanAndreas.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

GTASANANDREAS::GTASANANDREAS() : FPS(10), diners(nullptr)
{
    srand((time(NULL)));
    cargarConfiguracio();
    ampladaVista = 40;
    alturaVista = 20;
    inicialitzarMapa();
    inicialitzarJugador();
    inicialitzarPeatons();
    mostrarVista();

    while (true)
    {
        procesarInput();
        actualizar();
        Sleep(1000 / FPS);
    }
}

GTASANANDREAS::~GTASANANDREAS()
{
    Diners* actual = diners;
    while (actual != nullptr)
    {
        Diners* siguiente = actual->diners;
        delete actual;
        actual = siguiente;
    }

    if (mapa != nullptr)
    {
        for (int i = 0; i < config.altura; i++)
        {
            delete[] mapa[i];
        }
        delete[] mapa;
    }

    delete[] peatons;
}

void GTASANANDREAS::cargarConfiguracio()
{
    std::ifstream archivo("config.txt");
    if (archivo.is_open())
    {
        char separador;
        archivo >> config.amplada >> separador >> config.altura >> separador;
        archivo >> config.peatonsLosSantos >> separador >> config.peatgeLosSantos >> separador >> config.dinersMaxLosSantos >> separador;
        archivo >> config.peatonsSanFierro >> separador >> config.peatgeSanFierro >> separador >> config.dinersMaxSanFierro;
        archivo.close();
    }
    else
    {
        std::cout << "No es pot obrir el fitxer";
    }
    std::cout << config.amplada;
}

void GTASANANDREAS::inicialitzarMapa()
{
    mapa = new char* [config.altura];

    for (int i = 0; i < config.altura; i++)
    {
        mapa[i] = new char[config.amplada];
        for (int j = 0; j < config.amplada; j++)
        {
            mapa[i][j] = ' ';
        }
    }

    ampladaIsla = config.amplada / 3;
    for (int i = 0; i < config.altura; i++)
    {
        mapa[i][ampladaIsla] = 'X';
        mapa[i][ampladaIsla * 2] = 'X';

        if (i >= config.altura / 2 - 1 && i <= config.altura / 2 + 1)
        {
            mapa[i][ampladaIsla] = ' ';
            mapa[i][ampladaIsla * 2] = ' ';
        }
    }

    for (int j = 0; j < config.amplada; j++)
    {
        mapa[0][j] = 'X';
        mapa[config.altura - 1][j] = 'X';
    }
}

void GTASANANDREAS::inicialitzarJugador()
{
    jugador.posicio.x = config.amplada / 2;
    jugador.posicio.y = config.altura / 2;
    jugador.posAnterior = jugador.posicio;
    jugador.Direccio = '^';
    jugador.diners = 0;
}

void GTASANANDREAS::inicialitzarPeatons()
{
    cantitatPeatons = config.peatonsLosSantos + config.peatonsSanFierro;
    peatons = new Peatons[cantitatPeatons];

    for (int i = 0; i < config.peatonsLosSantos; i++)
    {
        peatons[i].posicio.x = 5 + rand() % (ampladaIsla - 10);
        peatons[i].posicio.y = 5 + rand() % (config.altura - 10);
        peatons[i].direccio = (rand() % 2 == 0) ? 'H' : 'V';
        peatons[i].viu = true;
        mapa[peatons[i].posicio.y][peatons[i].posicio.x] = 'P';
    }

    for (int i = 0; i < config.peatonsSanFierro; i++)
    {
        int index = config.peatonsLosSantos + i;
        peatons[index].posicio.x = ampladaIsla + 5 + rand() % (ampladaIsla - 10);
        peatons[index].posicio.y = 5 + rand() % (config.altura - 10);
        peatons[index].direccio = (rand() % 2 == 0) ? 'H' : 'V';
        peatons[index].viu = true;
        mapa[peatons[index].posicio.y][peatons[index].posicio.x] = 'P';
    }
}

void GTASANANDREAS::regenerarPeaton(int indice)
{
    if (peatons[indice].posicio.x < ampladaIsla)
    {
        peatons[indice].posicio.x = 5 + rand() % (ampladaIsla - 10);
    }
    else
    {
        peatons[indice].posicio.x = ampladaIsla + 5 + rand() % (ampladaIsla - 10);
    }
    peatons[indice].posicio.y = 5 + rand() % (config.altura - 10);
    peatons[indice].viu = true;
    mapa[peatons[indice].posicio.y][peatons[indice].posicio.x] = 'P';
}

bool GTASANANDREAS::estaCostatJugador(const Posicio& posPeaton)
{
    return (abs(jugador.posicio.x - posPeaton.x) + abs(jugador.posicio.y - posPeaton.y)) <= 3;
}

void GTASANANDREAS::mourePeatons()
{
    for (int i = 0; i < cantitatPeatons; i++)
    {
        if (!peatons[i].viu || estaCostatJugador(peatons[i].posicio))
        {
            continue;
        }

        mapa[peatons[i].posicio.y][peatons[i].posicio.x] = ' ';

        if (peatons[i].direccio == 'H')
        {
            int PeatoX = peatons[i].posicio.x + (rand() % 3 - 1);
            if (PeatoX > 0 && PeatoX < config.amplada - 1 && mapa[peatons[i].posicio.y][PeatoX] == ' ')
            {
                peatons[i].posicio.x = PeatoX;
            }
        }
        else
        {
            int PeatoY = peatons[i].posicio.y + (rand() % 3 - 1);
            if (PeatoY > 0 && PeatoY < config.altura - 1 && mapa[PeatoY][peatons[i].posicio.x] == ' ')
            {
                peatons[i].posicio.y = PeatoY;
            }
        }

        mapa[peatons[i].posicio.y][peatons[i].posicio.x] = 'P';
    }
}

void GTASANANDREAS::agregarDiners(Posicio pos, int cantidad)
{
    Diners* nuevo = new Diners;
    nuevo->posicio = pos;
    nuevo->cantitat = cantidad;
    nuevo->diners = diners;
    diners = nuevo;
}

void GTASANANDREAS::AtacJugador()
{
    if (GetAsyncKeyState(ATTACK_KEY))
    {
        for (int i = 0; i < cantitatPeatons; i++)
        {
            if (!peatons[i].viu) continue;

            if (abs(jugador.posicio.x - peatons[i].posicio.x) <= 1 && abs(jugador.posicio.y - peatons[i].posicio.y) <= 1)
            {
                peatons[i].viu = false;
                mapa[peatons[i].posicio.y][peatons[i].posicio.x] = ' ';

                int dinero = (peatons[i].posicio.x < ampladaIsla) ?
                    rand() % config.dinersMaxLosSantos + 1 :
                    rand() % config.dinersMaxSanFierro + 1;

                agregarDiners(peatons[i].posicio, dinero);
                regenerarPeaton(i);
            }
        }
    }
}

void GTASANANDREAS::recollirDiners()
{
    Diners* actual = diners;
    Diners* anterior = nullptr;

    while (actual != nullptr)
    {
        if (jugador.posicio.x == actual->posicio.x && jugador.posicio.y == actual->posicio.y)
        {
            jugador.diners += actual->cantitat;

            if (anterior == nullptr)
            {
                diners = actual->diners;
                delete actual;
                actual = diners;
            }
            else
            {
                anterior->diners = actual->diners;
                delete actual;
                actual = anterior->diners;
            }
        }
        else
        {
            anterior = actual;
            actual = actual->diners;
        }
    }
}

void GTASANANDREAS::procesarInput()
{
    jugador.posAnterior = jugador.posicio;

    if (GetAsyncKeyState('W') && jugador.posicio.y > 1 && mapa[jugador.posicio.y - 1][jugador.posicio.x] != 'X')
    {
        jugador.posicio.y--;
        jugador.Direccio = '^';
    }
    else if (GetAsyncKeyState('S') && jugador.posicio.y < config.altura - 2 && mapa[jugador.posicio.y + 1][jugador.posicio.x] != 'X')
    {
        jugador.posicio.y++;
        jugador.Direccio = 'v';
    }
    else if (GetAsyncKeyState('A') && jugador.posicio.x > 1 && mapa[jugador.posicio.y][jugador.posicio.x - 1] != 'X')
    {
        jugador.posicio.x--;
        jugador.Direccio = '<';
    }
    else if (GetAsyncKeyState('D') && jugador.posicio.x < config.amplada - 2 && mapa[jugador.posicio.y][jugador.posicio.x + 1] != 'X')
    {
        jugador.posicio.x++;
        jugador.Direccio = '>';
    }
}

void GTASANANDREAS::mostrarVista()
{
    system("cls");
    std::cout << "                 GTA SAN ANDREAS" << std::endl;

    mapa[jugador.posAnterior.y][jugador.posAnterior.x] = ' ';
    char jugadorOriginal = mapa[jugador.posicio.y][jugador.posicio.x];

    Diners* temp = diners;
    while (temp != nullptr)
    {
        mapa[temp->posicio.y][temp->posicio.x] = '$';
        temp = temp->diners;
    }

    mapa[jugador.posicio.y][jugador.posicio.x] = jugador.Direccio;

    int VistaX = jugador.posicio.x - ampladaVista / 2;
    int VistaY = jugador.posicio.y - alturaVista / 2;

    if (VistaX < 0) VistaX = 0;
    if (VistaY < 0) VistaY = 0;
    if (VistaX + ampladaVista > config.amplada) VistaX = config.amplada - ampladaVista;
    if (VistaY + alturaVista > config.altura) VistaY = config.altura - alturaVista;

    for (int i = VistaY; i < VistaY + alturaVista && i < config.altura; i++)
    {
        for (int j = VistaX; j < VistaX + ampladaVista && j < config.amplada; j++)
        {
            std::cout << mapa[i][j];
        }
        std::cout << '\n';
    }

    mapa[jugador.posicio.y][jugador.posicio.x] = jugadorOriginal;
    std::cout << "Diners: " << jugador.diners << std::endl;
}

void GTASANANDREAS::actualizar()
{
    AtacJugador();
    recollirDiners();
    mourePeatons();
    mostrarVista();
}