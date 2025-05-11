#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ATTACK_KEY VK_SPACE

// Configuració del joc
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

<<<<<<< HEAD
=======
//Per guardar posicions
>>>>>>> Peaton
struct Posicio
{
    int x;
    int y;
};

<<<<<<< HEAD
=======
//  Pels peatons
>>>>>>> Peaton
struct Peatons
{
    Posicio posicio;
    char direccio;
    bool viu;
};

// Estructura per al jugador
struct Jugador
{
    Posicio posicio;
    Posicio posAnterior;
    char Direccio;
    int diners;
};

// Estructura pels diners
struct Diners
{
    Posicio posicio;
<<<<<<< HEAD
    int cantidad;
};

struct GTASANANDREAS
{

=======
    int cantitat;
    Diners* diners;
};

// Struct principal del joc
struct GTASANANDREAS
{
>>>>>>> Peaton
    Config config;
    char** mapa;
    Jugador jugador;
    int ampladaIsla;
    Peatons* peatons;
    int cantitatPeatons;
    int ampladaVista;
<<<<<<< HEAD
    int anchuraVista;
    int FPS = 60;




    GTASANANDREAS()
    {
        cargarConfiguracio();
        inicialitzarMapa();
        inicialitzarJugador();

        mostrarMapaInicial();
        mapa[jugador.posicio.y][jugador.posicio.x] = jugador.Direccio;

=======
    int alturaVista;
    int FPS = 10;
    Diners* diners = nullptr;

    // Constructor
    GTASANANDREAS()
    {
        srand((time(NULL)));

        cargarConfiguracio();


        ampladaVista = 40;
        alturaVista = 20;


        inicialitzarMapa();
        inicialitzarJugador();
        inicialitzarPeatons();
        mostrarVista();

        // GameLopp
>>>>>>> Peaton
        while (true)
        {
            procesarInput();
            actualizar();
<<<<<<< HEAD
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

=======
            Sleep(1000 / FPS);
        }
    }

    // Destructor per allibera la memoria
    ~GTASANANDREAS()
    {
        // Libera diners
        Diners* actual = diners;
        while (actual != nullptr)
        {
            Diners* siguiente = actual->diners;
            delete actual;
            actual = siguiente;
        }

        // Libera mapa correctamente
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

    // Carrega la configuració
>>>>>>> Peaton
    void cargarConfiguracio()
    {
        std::ifstream archivo("config.txt");
        if (archivo.is_open())
        {
            char separador;
<<<<<<< HEAD
            archivo >> config.amplada >> separador >> config.altura;
            archivo >> config.peatonsLosSantos >> separador >> config.peatgeLosSantos >> separador >> config.dinersMaxLosSantos;
=======
            // Llegeix les dimensions del mapa
            archivo >> config.amplada >> separador >> config.altura >> separador;
            // Llegeix la configuració de Los Santos
            archivo >> config.peatonsLosSantos >> separador >> config.peatgeLosSantos >> separador >> config.dinersMaxLosSantos >> separador;
            // Llegeix la configuració de San Fierro
>>>>>>> Peaton
            archivo >> config.peatonsSanFierro >> separador >> config.peatgeSanFierro >> separador >> config.dinersMaxSanFierro;
            archivo.close();
        }
        else
        {
            std::cout << "No es pot obrir el fitxer";
        }
<<<<<<< HEAD
    }

    void inicialitzarMapa()
    {
        mapa = new char* [config.altura];

        for (int i = 0; i < config.altura; i++)
        {
            mapa[i] = new char[config.amplada];


=======

    }

    // Inicialitza el mapa del joc
    void inicialitzarMapa()
    {

        mapa = new char* [config.altura];


        for (int i = 0; i < config.altura; i++)
        {
            mapa[i] = new char[config.amplada];
>>>>>>> Peaton
            for (int j = 0; j < config.amplada; j++)
            {
                mapa[i][j] = ' ';
            }
        }


<<<<<<< HEAD

=======
>>>>>>> Peaton
        ampladaIsla = config.amplada / 3;
        for (int i = 0; i < config.altura; i++)
        {
            mapa[i][ampladaIsla] = 'X';
            mapa[i][ampladaIsla * 2] = 'X';

<<<<<<< HEAD
=======

>>>>>>> Peaton
            if (i >= config.altura / 2 - 1 && i <= config.altura / 2 + 1)
            {
                mapa[i][ampladaIsla] = ' ';
                mapa[i][ampladaIsla * 2] = ' ';
            }
        }

<<<<<<< HEAD
=======

>>>>>>> Peaton
        for (int j = 0; j < config.amplada; j++)
        {
            mapa[0][j] = 'X';
            mapa[config.altura - 1][j] = 'X';
        }
    }

<<<<<<< HEAD
=======
    // Inicialitza el jugador
>>>>>>> Peaton
    void inicialitzarJugador()
    {
        jugador.posicio.x = config.amplada / 2;
        jugador.posicio.y = config.altura / 2;
        jugador.posAnterior = jugador.posicio;
        jugador.Direccio = '^';
        jugador.diners = 0;
    }

<<<<<<< HEAD
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
=======
        jugador.posicio.x = config.amplada / 2;
        jugador.posicio.y = config.altura / 2;
        jugador.posAnterior = jugador.posicio;
        jugador.Direccio = '^';
        jugador.diners = 0;
    }

    // Inicialitza els peatons
    void inicialitzarPeatons()
    {
        // Calcula el total de peatons
        cantitatPeatons = config.peatonsLosSantos + config.peatonsSanFierro;
        peatons = new Peatons[cantitatPeatons];

        // Peatons de Los Santos
        for (int i = 0; i < config.peatonsLosSantos; i++)
        {
            peatons[i].posicio.x = 5 + rand() % (ampladaIsla - 10);  // Posició aleatòria dins Los Santos
            peatons[i].posicio.y = 5 + rand() % (config.altura - 10);
            peatons[i].direccio = rand() % 2 == 0 ? 'H' : 'V';     // Direcció aleatòria
            peatons[i].viu = true;
            mapa[peatons[i].posicio.y][peatons[i].posicio.x] = 'P';
        }

        // Peatons de San Fierro
        for (int i = 0; i < config.peatonsSanFierro; i++)
        {
            int index = config.peatonsLosSantos + i;
            peatons[index].posicio.x = ampladaIsla + 5 + rand() % (ampladaIsla - 10);  // Posició aleatòria dins San Fierro
            peatons[index].posicio.y = 5 + rand() % (config.altura - 10);
            peatons[index].direccio = rand() % 2 == 0 ? 'H' : 'V';  // Direcció aleatòria
            peatons[index].viu = true;
            mapa[peatons[index].posicio.y][peatons[index].posicio.x] = 'P';
>>>>>>> Peaton
        }
    }



<<<<<<< HEAD
    void mostrarMapaInicial()
=======


    bool estaCostatJugador(const Posicio& posPeaton)
    {

        return (abs(jugador.posicio.x - posPeaton.x) + abs(jugador.posicio.y - posPeaton.y)) <= 3;
    }


    void mourePeatons()
    {
        for (int i = 0; i < cantitatPeatons; i++)
        {
            if (!peatons[i].viu || estaCostatJugador(peatons[i].posicio))
            {
                continue;  // Salta els peatons morts o a prop del jugador ja que no cal
            }

            // Esborra la posicio anterior del peató amb ' '
            mapa[peatons[i].posicio.y][peatons[i].posicio.x] = ' ';

            if (peatons[i].direccio == 'H')//si es 'H' el peato va en horizontal
            {

                int PeatoX = peatons[i].posicio.x + (rand() % 3 - 1); // -1, 0 o 1,esquerra o d
                if (PeatoX > 0 && PeatoX < config.amplada - 1 && mapa[peatons[i].posicio.y][PeatoX] == ' ')
                {
                    peatons[i].posicio.x = PeatoX;
                }
            }
            else
            {
                // Moviment vertical simple
                int PeatoY = peatons[i].posicio.y + (rand() % 3 - 1); // -1, 0 o 1
                if (PeatoY > 0 && PeatoY < config.altura - 1 && mapa[PeatoY][peatons[i].posicio.x] == ' ')
                {
                    peatons[i].posicio.y = PeatoY;
                }
            }

            // Actualitza la nova posicio al mapa amb 'P'
            mapa[peatons[i].posicio.y][peatons[i].posicio.x] = 'P';
        }
    }



    void AtacJugador()
    {
        if (GetAsyncKeyState(ATTACK_KEY))
        {
            for (int i = 0; i < cantitatPeatons; i++)
            {
                if (!peatons[i].viu)
                {
                    continue;  //si el peato ja esta mort, no cal i es pot saltar
                }


                if (abs(jugador.posicio.x - peatons[i].posicio.x) <= 1 && abs(jugador.posicio.y - peatons[i].posicio.y) <= 1)
                {
                    //matar al peato
                    peatons[i].viu = false;
                    mapa[peatons[i].posicio.y][peatons[i].posicio.x] = ' ';

                    //Diners aleatori
                    int dinero = (peatons[i].posicio.x < ampladaIsla) ? rand() % config.dinersMaxLosSantos + 1 : rand() % config.dinersMaxSanFierro + 1;


                }
            }
        }
    }




    void procesarInput()
    {

        jugador.posAnterior = jugador.posicio;

        // Moviment cap adalt
        if (GetAsyncKeyState('W') && jugador.posicio.y > 1)
        {
            if (mapa[jugador.posicio.y - 1][jugador.posicio.x] != 'X')
            {
                jugador.posicio.y--;
                jugador.Direccio = '^';
            }
        }
        // Moviment cap avall
        else if (GetAsyncKeyState('S') && jugador.posicio.y < config.altura - 2)
        {
            if (mapa[jugador.posicio.y + 1][jugador.posicio.x] != 'X')
            {
                jugador.posicio.y++;
                jugador.Direccio = 'v';
            }
        }
        // Moviment cap a l'esquerra
        else if (GetAsyncKeyState('A') && jugador.posicio.x > 1)
        {
            if (mapa[jugador.posicio.y][jugador.posicio.x - 1] != 'X')
            {
                jugador.posicio.x--;
                jugador.Direccio = '<';
            }
        }
        // Moviment cap a la dreta
        else if (GetAsyncKeyState('D') && jugador.posicio.x < config.amplada - 2)
        {
            if (mapa[jugador.posicio.y][jugador.posicio.x + 1] != 'X')
            {
                jugador.posicio.x++;
                jugador.Direccio = '>';
            }
        }
    }


    void mostrarVista()
>>>>>>> Peaton
    {
        system("cls");
        std::cout << "                 GTA SAN ANDREAS" << std::endl;

<<<<<<< HEAD
        mapa[jugador.posAnterior.y][jugador.posAnterior.x] = ' '; //posicio anterior del jugador en blanc

        char jugadorOriginal = mapa[jugador.posicio.y][jugador.posicio.x];
        mapa[jugador.posicio.y][jugador.posicio.x] = jugador.Direccio;

        for (int i = 0; i < config.altura; i++)
        {
            for (int j = 0; j < config.amplada; j++)
=======
        // Posició anterior del jugador amb ' ' per borrar-ho
        mapa[jugador.posAnterior.y][jugador.posAnterior.x] = ' ';

        // Guarda jugador
        char jugadorOriginal = mapa[jugador.posicio.y][jugador.posicio.x];

        // Usa una variable temporal para diners
        Diners* temp = diners;
        while (temp != nullptr)
        {
            mapa[temp->posicio.y][temp->posicio.x] = '$';
            temp = temp->diners;
        }

        // Afegir el jugador al mapa
        mapa[jugador.posicio.y][jugador.posicio.x] = jugador.Direccio;

        // La vista del jugador
        int VistaX = jugador.posicio.x - ampladaVista / 2;
        int VistaY = jugador.posicio.y - alturaVista / 2;

        // Limits del mapa
        if (VistaX < 0)
        {
            VistaX = 0;
        }
        if (VistaY < 0)
        {
            VistaY = 0;
        }
        if (VistaX + ampladaVista > config.amplada)
        {
            VistaX = config.amplada - ampladaVista;
        }
        if (VistaY + alturaVista > config.altura)
        {
            VistaY = config.altura - alturaVista;
        }

        // Mostrar només la vista del jugador
        for (int i = VistaY; i < VistaY + alturaVista && i < config.altura; i++)
        {
            for (int j = VistaX; j < VistaX + ampladaVista && j < config.amplada; j++)
>>>>>>> Peaton
            {
                std::cout << mapa[i][j];
            }
            std::cout << '\n';
        }

<<<<<<< HEAD

        mapa[jugador.posicio.y][jugador.posicio.x] = jugadorOriginal;

        std::cout << "Diners: " << jugador.diners << std::endl;
    }

    void actualizar()
    {
        procesarInput();
        mostrarMapaInicial();

    }



=======
        // Restaura jugador
        mapa[jugador.posicio.y][jugador.posicio.x] = jugadorOriginal;

        // Mostrar els diners abaix per saber quan té tot el moment
        std::cout << "Diners: " << jugador.diners << std::endl;
    }

    //actualitzar el joc per el GameLoop
    void actualizar()
    {
        AtacJugador();
        mourePeatons();
        mostrarVista();
    }
>>>>>>> Peaton
};
int main()
{
    GTASANANDREAS juego;
<<<<<<< HEAD

=======
>>>>>>> Peaton
}