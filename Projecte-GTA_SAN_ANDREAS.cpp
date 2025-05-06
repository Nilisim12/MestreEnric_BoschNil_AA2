#include <iostream>

class Person
{
public:
    int x;
    int y;
};

int main()
{
    int rows = 5, columns = 17;
    char** mapa;

    mapa = new char* [rows];

    for (int i = 0; rows > i; i++)
    {
        mapa[i] = new char[columns];
    }

    for (int i = 0; rows > i; i++)
    {
        for (int j = 0; columns > j; j++)
        {
            mapa[i][j] = '_';
        }
    }

    for (int i = 0; rows > i; i++)
    {
        for (int j = 0; columns > j; j++)
        {
            std::cout << mapa[i][j];
        }
        std::cout << std::endl;
    }

    for (int i = 0; rows > i; i++)
    {
        delete[] mapa[i];
    }
    delete[] mapa;
}
