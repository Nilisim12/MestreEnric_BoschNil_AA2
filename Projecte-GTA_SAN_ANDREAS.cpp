#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <vector>
#include <algorithm>


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
    bool operator==(const Posicio& other) const {
        return x == other.x && y == other.y;
    }
};

struct Peato
{
    Posicio posicio;
    Posicio posAnterior;
    char direccio;
    bool viu;
    bool movimentPausat;
    int isla; // 0: Los Santos, 1: San Fierro, 2: Las Venturas
};

struct Jugador
{
    Posicio posicio;
    Posicio posAnterior;
    char Direccio;
    int diners;
};

struct Diners
{
    Posicio posicio;
    int quantitat;
    int isla;
};

struct GTASANANDREAS
{
    Config config;
    char** mapa;
    Jugador jugador;
    int ampladaIsla;
    std::vector<Peato> peatons;
    std::vector<Diners> dinersTerra;
    int ampladaVista;
    int alturaVista;
    int FPS = 144;
    bool mostrarVistaCompleta = false;

    GTASANANDREAS()
    {
        srand(static_cast<unsigned>(time(NULL)));
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

    void inicialitzarJugador()
    {
        jugador.posicio.x = config.amplada / 2;
        jugador.posicio.y = config.altura / 2;
        jugador.posAnterior = jugador.posicio;
        jugador.Direccio = '^';
        jugador.diners = 0;
    }

    void inicialitzarPeatons()
    {
        // Peatones en Los Santos
        for (int i = 0; i < config.peatonsLosSantos; i++)
        {
            afegirPeato(0);
        }

        // Peatones en San Fierro
        for (int i = 0; i < config.peatonsSanFierro; i++)
        {
            afegirPeato(1);
        }
    }

    void afegirPeato(int isla)
    {
        Peato nouPeato;
        nouPeato.viu = true;
        nouPeato.movimentPausat = false;
        nouPeato.isla = isla;

        // Generar posición aleatoria en la isla correspondiente
        int minX, maxX;
        if (isla == 0) // Los Santos
        {
            minX = 1;
            maxX = ampladaIsla - 1;
        }
        else if (isla == 1) // San Fierro
        {
            minX = ampladaIsla + 1;
            maxX = ampladaIsla * 2 - 1;
        }
        else // Las Venturas
        {
            minX = ampladaIsla * 2 + 1;
            maxX = config.amplada - 2;
        }

        nouPeato.posicio.x = minX + rand() % (maxX - minX + 1);
        nouPeato.posicio.y = 1 + rand() % (config.altura - 2);
        nouPeato.posAnterior = nouPeato.posicio;

        // Dirección aleatoria (arriba, abajo, izquierda, derecha)
        int dir = rand() % 4;
        switch (dir)
        {
        case 0: nouPeato.direccio = '^'; break;
        case 1: nouPeato.direccio = 'v'; break;
        case 2: nouPeato.direccio = '<'; break;
        case 3: nouPeato.direccio = '>'; break;
        }

        peatons.push_back(nouPeato);
    }

    void mourePeato(Peato& peato)
    {
        if (!peato.viu || peato.movimentPausat) return;

        peato.posAnterior = peato.posicio;

        // Verificar si el jugador está cerca (a 1 casilla de distancia)
        int distanciaX = abs(jugador.posicio.x - peato.posicio.x);
        int distanciaY = abs(jugador.posicio.y - peato.posicio.y);
        if (distanciaX <= 1 && distanciaY <= 1)
        {
            peato.movimentPausat = true;
            return;
        }
        else
        {
            peato.movimentPausat = false;
        }

        // Intentar mover en la dirección actual
        Posicio novaPos = peato.posicio;
        switch (peato.direccio)
        {
        case '^': novaPos.y--; break;
        case 'v': novaPos.y++; break;
        case '<': novaPos.x--; break;
        case '>': novaPos.x++; break;
        }

        // Verificar si puede moverse
        bool puedeMover = true;
        if (novaPos.x <= 0 || novaPos.x >= config.amplada - 1 ||
            novaPos.y <= 0 || novaPos.y >= config.altura - 1 ||
            mapa[novaPos.y][novaPos.x] == 'X')
        {
            puedeMover = false;
        }

        // Si no puede moverse, cambiar de dirección
        if (!puedeMover)
        {
            // Elegir una nueva dirección aleatoria
            int nuevaDir = rand() % 4;
            switch (nuevaDir)
            {
            case 0: peato.direccio = '^'; break;
            case 1: peato.direccio = 'v'; break;
            case 2: peato.direccio = '<'; break;
            case 3: peato.direccio = '>'; break;
            }
            return;
        }

        // Mover el peaton
        peato.posicio = novaPos;
    }

    void procesarInput()
    {
        jugador.posAnterior = jugador.posicio;

        if (GetAsyncKeyState('W') & 0x8000 && jugador.posicio.y > 1)
        {
            if (mapa[jugador.posicio.y - 1][jugador.posicio.x] != 'X')
            {
                jugador.posicio.y--;
                jugador.Direccio = '^';
            }
        }
        else if (GetAsyncKeyState('S') & 0x8000 && jugador.posicio.y < config.altura - 2)
        {
            if (mapa[jugador.posicio.y + 1][jugador.posicio.x] != 'X')
            {
                jugador.posicio.y++;
                jugador.Direccio = 'v';
            }
        }
        else if (GetAsyncKeyState('A') & 0x8000 && jugador.posicio.x > 1)
        {
            if (mapa[jugador.posicio.y][jugador.posicio.x - 1] != 'X')
            {
                jugador.posicio.x--;
                jugador.Direccio = '<';
            }
        }
        else if (GetAsyncKeyState('D') & 0x8000 && jugador.posicio.x < config.amplada - 2)
        {
            if (mapa[jugador.posicio.y][jugador.posicio.x + 1] != 'X')
            {
                jugador.posicio.x++;
                jugador.Direccio = '>';
            }
        }
        else if (GetAsyncKeyState('M') & 0x8000)
        {
            mostrarVistaCompleta = !mostrarVistaCompleta;
            Sleep(200); // Pequeño delay para evitar múltiples toques
        }
        else if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            atacar();
            Sleep(200); // Pequeño delay para evitar múltiples toques
        }
    }

    void atacar()
    {
        // Verificar si hay algún peaton adyacente al jugador
        for (auto& peato : peatons)
        {
            if (!peato.viu) continue;

            int distanciaX = abs(jugador.posicio.x - peato.posicio.x);
            int distanciaY = abs(jugador.posicio.y - peato.posicio.y);

            // Atacar en la dirección que mira el jugador
            bool ataqueExitoso = false;
            switch (jugador.Direccio)
            {
            case '^':
                ataqueExitoso = (peato.posicio.x == jugador.posicio.x && peato.posicio.y == jugador.posicio.y - 1);
                break;
            case 'v':
                ataqueExitoso = (peato.posicio.x == jugador.posicio.x && peato.posicio.y == jugador.posicio.y + 1);
                break;
            case '<':
                ataqueExitoso = (peato.posicio.y == jugador.posicio.y && peato.posicio.x == jugador.posicio.x - 1);
                break;
            case '>':
                ataqueExitoso = (peato.posicio.y == jugador.posicio.y && peato.posicio.x == jugador.posicio.x + 1);
                break;
            }

            if (ataqueExitoso)
            {
                // Matar al peaton
                peato.viu = false;

                // Añadir dinero al suelo
                Diners nouDiners;
                nouDiners.posicio = peato.posicio;
                nouDiners.isla = peato.isla;

                if (peato.isla == 0) // Los Santos
                    nouDiners.quantitat = 1 + rand() % config.dinersMaxLosSantos;
                else if (peato.isla == 1) // San Fierro
                    nouDiners.quantitat = 1 + rand() % config.dinersMaxSanFierro;
                else // Las Venturas (si se implementa)
                    nouDiners.quantitat = 1 + rand() % 100; // Valor por defecto

                dinersTerra.push_back(nouDiners);

                // Regenerar peaton en la misma isla
                afegirPeato(peato.isla);

                break; // Solo atacar a un peaton a la vez
            }
        }
    }

    void recollirDiners()
    {
        for (auto it = dinersTerra.begin(); it != dinersTerra.end(); )
        {
            if (jugador.posicio == it->posicio)
            {
                jugador.diners += it->quantitat;
                it = dinersTerra.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void mostrarMapaInicial()
    {
        system("cls");

        // Limpiar posición anterior del jugador
        mapa[jugador.posAnterior.y][jugador.posAnterior.x] = ' ';

        // Limpiar posición anterior de los peatones
        for (auto& peato : peatons)
        {
            if (peato.viu)
            {
                mapa[peato.posAnterior.y][peato.posAnterior.x] = ' ';
            }
        }

        // Dibujar dinero en el suelo
        for (auto& diners : dinersTerra)
        {
            mapa[diners.posicio.y][diners.posicio.x] = '$';
        }

        // Dibujar peatones vivos
        for (auto& peato : peatons)
        {
            if (peato.viu)
            {
                mapa[peato.posicio.y][peato.posicio.x] = 'P';
            }
        }

        // Guardar el carácter original donde está el jugador
        char jugadorOriginal = mapa[jugador.posicio.y][jugador.posicio.x];

        // Dibujar jugador
        mapa[jugador.posicio.y][jugador.posicio.x] = jugador.Direccio;

        // Mostrar el mapa
        for (int i = 0; i < config.altura; i++)
        {
            for (int j = 0; j < config.amplada; j++)
            {
                std::cout << mapa[i][j];
            }
            std::cout << '\n';
        }

        // Restaurar el carácter original donde está el jugador
        mapa[jugador.posicio.y][jugador.posicio.x] = jugadorOriginal;

        std::cout << "Diners: " << jugador.diners << std::endl;
        std::cout << "Posicio: (" << jugador.posicio.x << ", " << jugador.posicio.y << ")" << std::endl;
    }

    void mostrarVista()
    {
        system("cls");
        std::cout << "                 GTA SAN ANDREAS" << std::endl;

        if (mostrarVistaCompleta)
        {
            mostrarMapaInicial();
            return;
        }

        // Calcular los límites de la vista
        int minX = (jugador.posicio.x - ampladaVista / 2) < 0 ? 0 : (jugador.posicio.x - ampladaVista / 2);
        int maxX = (jugador.posicio.x + ampladaVista / 2) > (config.amplada - 1) ? (config.amplada - 1) : (jugador.posicio.x + ampladaVista / 2);
        int minY = (jugador.posicio.y - alturaVista / 2) < 0 ? 0 : (jugador.posicio.y - alturaVista / 2);
        int maxY = (jugador.posicio.y + alturaVista / 2) > (config.altura - 1) ? (config.altura - 1) : (jugador.posicio.y + alturaVista / 2);

        // Limpiar posición anterior del jugador
        if (jugador.posAnterior.y >= minY && jugador.posAnterior.y <= maxY &&
            jugador.posAnterior.x >= minX && jugador.posAnterior.x <= maxX)
        {
            mapa[jugador.posAnterior.y][jugador.posAnterior.x] = ' ';
        }

        // Limpiar posición anterior de los peatones
        for (auto& peato : peatons)
        {
            if (peato.viu &&
                peato.posAnterior.y >= minY && peato.posAnterior.y <= maxY &&
                peato.posAnterior.x >= minX && peato.posAnterior.x <= maxX)
            {
                mapa[peato.posAnterior.y][peato.posAnterior.x] = ' ';
            }
        }

        // Dibujar dinero en el suelo
        for (auto& diners : dinersTerra)
        {
            if (diners.posicio.y >= minY && diners.posicio.y <= maxY &&
                diners.posicio.x >= minX && diners.posicio.x <= maxX)
            {
                mapa[diners.posicio.y][diners.posicio.x] = '$';
            }
        }

        // Dibujar peatones vivos
        for (auto& peato : peatons)
        {
            if (peato.viu &&
                peato.posicio.y >= minY && peato.posicio.y <= maxY &&
                peato.posicio.x >= minX && peato.posicio.x <= maxX)
            {
                mapa[peato.posicio.y][peato.posicio.x] = 'P';
            }
        }

        // Guardar el carácter original donde está el jugador
        char jugadorOriginal = mapa[jugador.posicio.y][jugador.posicio.x];

        // Dibujar jugador
        mapa[jugador.posicio.y][jugador.posicio.x] = jugador.Direccio;

        // Mostrar la vista
        for (int i = minY; i <= maxY; i++)
        {
            for (int j = minX; j <= maxX; j++)
            {
                std::cout << mapa[i][j];
            }
            std::cout << '\n';
        }

        // Restaurar el carácter original donde está el jugador
        mapa[jugador.posicio.y][jugador.posicio.x] = jugadorOriginal;

        std::cout << "Diners: " << jugador.diners << std::endl;
        std::cout << "Posicio: (" << jugador.posicio.x << ", " << jugador.posicio.y << ")" << std::endl;
        std::cout << "Tecla M: Mostrar mapa completo" << std::endl;
        std::cout << "Espacio: Atacar" << std::endl;
    }

    void actualizar()
    {
        // Moure cada peató
        for (auto& peato : peatons)
        {
            mourePeato(peato);
        }

        // Recollir diners si el jugador passa per sobre
        recollirDiners();

        // Mostrar la vista actualitzada
        mostrarVista();
    }
};

int main()
{
    GTASANANDREAS juego;
    return 0;
}