#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

struct Config
{
    int amplada = 50;
    int altura = 30;
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

struct GTASANANDREAS
{
    Config config;
    char** mapa;
    int ampladaIsla;
    int FPS = 60;

    GTASANANDREAS()
    {
        cargarConfiguracio();
        inicialitzarMapa();
        mostrarMapaInicial();

        while (true)
        {
            Sleep(1000 / FPS);
        }
    }

    ~GTASANANDREAS()
    {
        for (int i = 0; i < config.altura; i++)
        {
            delete[] mapa[i];
        }
        delete[] mapa;
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

    void mostrarMapaInicial()
    {
        system("cls");
        std::cout << "                 GTA SAN ANDREAS" << std::endl;

        for (int i = 0; i < config.altura; i++)
        {
            for (int j = 0; j < config.amplada; j++)
            {
                std::cout << mapa[i][j];
            }
            std::cout << '\n';
        }
    }
};

int main()
{
    GTASANANDREAS juego;
}