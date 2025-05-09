#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

struct Config
{
    int amplada;
    int altura;
    int peatonsLosSantos;
    int peatgeLosSantos;
    int dinersMaxLosSantos;
    int peatonsSanFierro;
    int peatgeSanFierro;
    int dinersMaxSanFierro;
};

struct Posicio
{
    int x;
    int y;
};

struct Peatons
{
    Posicio posicio;
    char direccio;
    bool viu;
};

struct Jugador
{
    Posicio posicio;
    Posicio posAnterior;
    char Direccio;
    int diners;
};

struct Dinero
{
    Posicio posicio;
    int cantidad;
};

struct GTASANANDREAS
{

    Config config;
    char** mapa;
    Jugador jugador;
    int ampladaIsla;
    Peatons* peatons;
    int cantitatPeatons;
    int ampladaVista;
    int anchuraVista;
    int FPS = 60;




    GTASANANDREAS()
    {
        cargarConfiguracio();
        inicialitzarMapa();
        inicialitzarJugador();

        mostrarMapaInicial();
        mapa[jugador.posicio.y][jugador.posicio.x] = jugador.Direccio;

        while (true)
        {
            procesarInput();
            actualizar();
            Sleep(1);
        }
    }

    ~GTASANANDREAS()
    {
        for (int i = 0; i < config.altura; i++)
        {
            delete[] mapa[i];
        }
        delete[] mapa;
        delete[] peatons;

    }

    void cargarConfiguracio()
    {
        std::ifstream archivo("config.txt");
        if (archivo.is_open())
        {
            char separador;
            archivo >> config.amplada >> separador >> config.altura;
            archivo >> config.peatonsLosSantos >> separador >> config.peatgeLosSantos >> separador >> config.dinersMaxLosSantos;
            archivo >> config.peatonsSanFierro >> separador >> config.peatgeSanFierro >> separador >> config.dinersMaxSanFierro;
            archivo.close();
        }
        else
        {
            std::cout << "No es pot obrir el fitxer";
        }
    }

    void inicialitzarMapa()
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

    void inicialitzarJugador()
    {
        jugador.posicio.x = config.amplada / 2;
        jugador.posicio.y = config.altura / 2;
        jugador.posAnterior = jugador.posicio;
        jugador.Direccio = '^';
        jugador.diners = 0;
    }

    void procesarInput()
    {
        jugador.posAnterior = jugador.posicio;

        if (GetAsyncKeyState('W') && jugador.posicio.y > 1)
        {
            jugador.posicio.y--;
            jugador.Direccio = '^';
        }
        else if (GetAsyncKeyState('S') && jugador.posicio.y < config.altura - 2)
        {
            jugador.posicio.y++;
            jugador.Direccio = 'v';
        }
        else if (GetAsyncKeyState('A') && jugador.posicio.x > 1)
        {
            jugador.posicio.x--;
            jugador.Direccio = '<';
        }
        else if (GetAsyncKeyState('D') && jugador.posicio.x < config.amplada - 2)
        {
            jugador.posicio.x++;
            jugador.Direccio = '>';
        }
    }



    void mostrarMapaInicial()
    {
        system("cls");
        std::cout << "                 GTA SAN ANDREAS" << std::endl;

        mapa[jugador.posAnterior.y][jugador.posAnterior.x] = ' '; //posicio anterior del jugador en blanc

        char jugadorOriginal = mapa[jugador.posicio.y][jugador.posicio.x];
        mapa[jugador.posicio.y][jugador.posicio.x] = jugador.Direccio;

        for (int i = 0; i < config.altura; i++)
        {
            for (int j = 0; j < config.amplada; j++)
            {
                std::cout << mapa[i][j];
            }
            std::cout << '\n';
        }


        mapa[jugador.posicio.y][jugador.posicio.x] = jugadorOriginal;

        std::cout << "Diners: " << jugador.diners << std::endl;
    }

    void actualizar()
    {
        procesarInput();
        mostrarMapaInicial();

    }



};

int main()
{
    GTASANANDREAS juego;

}