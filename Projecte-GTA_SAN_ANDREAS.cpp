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
    int** mapa;

    mapa = new int* [rows];

    for (int i = 0; rows > i; i++)
    {
        mapa[i] = new int[columns];
    }

    for (int i = 0; rows > i; i++)
    {
        for (int j = 0; columns > j; j++)
        {
            mapa[i][j] = "_";
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
}
