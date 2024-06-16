
#include "Snake.h"
#include "ncurses.h"
#include <algorithm>
#define SNAKE_LENGTH 3

Snake::Snake(int x, int y) {
    poison_count = 0;
    growth_count = 0;
    reverse_count = 0;
    gate_count = 0;
    direction = 'a';
    length = SNAKE_LENGTH;
    max_length = SNAKE_LENGTH;
    for (int i = 0; i < SNAKE_LENGTH ; i++)
        body.push_back(pair<int, int>(x+i, y));
}
pair<int, int> Snake::get_direction() {
    switch (getch()) {
        case 'w':
            direction = 'w';
            return {0, -1};
        case 's':
            direction = 's';
            return {0, 1};
        case 'd':
            direction = 'd';
            return {1, 0};
        case 'a':
            direction = 'a';
            return {-1, 0};
    }
    switch (direction) {
        case 'w':
            return {0, -1};
        case 's':
            return {0, 1};
        case 'd':
            return {1, 0};
        case 'a':
            return {-1, 0};
        default:
            return {0, 0};
    }
}
void Snake::move() {
    if (length >= body.size()) {
        pair<int, int> diff = Snake::get_direction();
        body.insert(body.begin(),
                    {body.front().first+diff.first, body.front().second+diff.second});
        if (length == body.size()-1) {
            body.pop_back();
        }
    }
    else if (length < body.size()) {
        body.pop_back();
    }
}
void Snake::growth() {
    growth_count++;
    length++;
    if (length > max_length)
        max_length = length;
}
void Snake::reverse() {
    std::reverse(body.begin(), body.end());
    reverse_count++;
    if (direction == 'w')
        direction = 's';
    else if (direction == 's')
        direction = 'w';
    else if (direction == 'a')
        direction = 'd';
    else if (direction == 'd')
        direction = 'a';
}
void Snake::poison() {
    poison_count++;
    length--;
}
bool Snake::isDead() {

    // 길이가 3밑으로 떨어졌는가?
    if (length < 3)
        return true;

    // 몸끼리 충돌이 일어났는가?
    for (int i = 1 ; i < body.size() ; i++){
        if (body[0].first == body[i].first && body[0].second == body[i].second )
            return true;
    }
    return false;
}
