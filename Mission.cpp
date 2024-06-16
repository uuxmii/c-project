
#include "Mission.h"
#include "Snake.h"

Mission::Mission(int length, int gate_count, int growth_count, int poison_count, int reverse_count) :
length(length), gate_count(gate_count), growth_count(growth_count), poison_count(poison_count), reverse_count(reverse_count){}

bool Mission::is_complete(Snake snake) {
    return snake.reverse_count >= reverse_count &&
            snake.max_length >= length &&
            snake.poison_count >= poison_count &&
            snake.growth_count >= growth_count &&
            snake.gate_count >= gate_count;
}

Mission::Mission() {

}
