#ifndef GAME_TRUCO
#define GAME_TRUCO
#include <iostream>


#include <stdlib.h>
#include <string.h>
using namespace std;
class Truco{
    private:
        enum naipes {copa, ouro, espada, paus};
        int cartas[4][12];
    public:
        void Distribui();
};
#endif
