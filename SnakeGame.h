

#ifndef SNAKEGAME_SNAKEGAME_H
#define SNAKEGAME_SNAKEGAME_H
#include "Snake.h"
#include "Stage.h"
#include "Gate.h"
#include "Screen.h"


class SnakeGame {
    int current;
    Gate gateA, gateB;
    Screen screen;
    Stage stage[4];
    Mission mission[4];
    Snake snake;
public:
    SnakeGame();
    void start();

};


#endif //SNAKEGAME_SNAKEGAME_H
