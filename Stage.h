
#ifndef SNAKEGAME_STAGE_H
#define SNAKEGAME_STAGE_H

#define MAP_SIZE 21


class Stage {
public:
    int map[MAP_SIZE][MAP_SIZE];
    Stage();
    int getTileType(int x, int y);
    void setTile(int x, int y, int type);
    bool isGrowth(int x, int y);
    bool isPoison(int x, int y);
    bool isGate(int x, int y);
    bool isWall(int x, int y);
    bool isReverse(int x, int y);
};


#endif //SNAKEGAME_STAGE_H
