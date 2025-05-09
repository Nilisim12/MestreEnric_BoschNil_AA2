#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

struct Config
{
    int ancho = 50;
    int alto = 25;
    int peatonesLosSantos;
    int peajeLosSantos;
    int dineroMaxLosSantos;
    int peatonesSanFierro;
    int peajeSanFierro;
    int dineroMaxSanFierro;
};

struct Posicion
{
    int x;
    int y;
};

struct Peaton
{
    Posicion pos;
    char direccion;
    bool vivo;
};

struct Jugador
{
    Posicion pos;
    char mirandoHacia;
    int dinero;
};

struct Dinero
{
    Posicion pos;
    int cantidad;
};

class GTASANANDREAS
{
private:
    Config config;
    char** mapa;
    Jugador jugador;
    Peaton* peatones;
    int cantidadPeatones;
    Dinero* dineroEnSuelo;
    int cantidadDinero;
    int islaActual;
    int anchoVista;
    int altoVista;

    void cargarConfiguracion()
    {

        std::ifstream archivo("config.txt");
        if (archivo.is_open())
        {
            char separador;
            archivo >> config.ancho >> separador >> config.alto;
            archivo >> config.peatonesLosSantos >> separador >> config.peajeLosSantos >> separador >> config.dineroMaxLosSantos;
            archivo >> config.peatonesSanFierro >> separador >> config.peajeSanFierro >> separador >> config.dineroMaxSanFierro;
            archivo.close();
        }
    }

    void inicializarMapa()
    {
        mapa = new char* [config.alto];
        for (int i = 0; i < config.alto; i++)
        {
            mapa[i] = new char[config.ancho];
            for (int j = 0; j < config.ancho; j++)
            {
                mapa[i][j] = ' ';
            }
        }


        int anchoIsla = config.ancho / 3;
        for (int i = 0; i < config.alto; i++)
        {
            mapa[i][anchoIsla] = '|';
            mapa[i][anchoIsla * 2] = '|';


            if (i >= config.alto / 2 - 1 && i <= config.alto / 2 + 1)
            {
                mapa[i][anchoIsla] = '=';
                mapa[i][anchoIsla * 2] = '=';
            }
        }


        for (int j = 0; j < config.ancho; j++)
        {
            mapa[0][j] = '-';
            mapa[config.alto - 1][j] = '-';
        }
    }

    void mostrarMapa()
    {

        std::cout << "                 GTA SAN ANDREAS" << std::endl;
        for (int i = 0; i < config.alto; i++)
        {
            for (int j = 0; j < config.ancho; j++)
            {
                std::cout << mapa[i][j];
            }
            std::cout << '\n';
        }
    }

public:
    GTASANANDREAS()
    {
        cargarConfiguracion();
        inicializarMapa();
        mostrarMapa();

    }

    ~GTASANANDREAS()
    {
        for (int i = 0; i < config.alto; i++)
        {
            delete[] mapa[i];
        }
        delete[] mapa;
        delete[] peatones;
        delete[] dineroEnSuelo;
    }
};

int main()
{
    GTASANANDREAS juego;


}