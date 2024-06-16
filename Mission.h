

#ifndef SNAKEGAME_MISSION_H
#define SNAKEGAME_MISSION_H


#include "Snake.h"

class Mission {
public:
    Mission();
    Mission(int length, int gate_count, int growth_count, int poison_count, int reverse_count);

    int length;
    int growth_count;
    int gate_count;
    int poison_count;
    int reverse_count;

    bool is_complete(Snake snake);
};


#endif //SNAKEGAME_MISSION_H
