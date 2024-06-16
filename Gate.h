

#ifndef SNAKEGAME_GATE_H
#define SNAKEGAME_GATE_H


class Gate {
public:
    Gate();

    int gate_x, gate_y;
    Gate *other;
    Gate(int x, int y);
};


#endif //SNAKEGAME_GATE_H
