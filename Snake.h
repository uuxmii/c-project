
#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME_SNAKE_H
#include <vector>
using namespace std;
class Snake {
public:
    vector<pair<int, int>> body;
    int length;
    char direction;
    int growth_count, poison_count;
    Snake(int x=11, int y=11);
    pair<int, int> get_direction();
    void move();
    void growth();
    void poison();
    bool isDead();

    void reverse();

    int reverse_count;
    int max_length;
    int gate_count;
};


#endif //SNAKEGAME_SNAKE_H
