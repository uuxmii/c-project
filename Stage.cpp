
#include "Stage.h"
// 0 = 공기
// 1 = 벽
// 2 = 모서리
// 3 = 성장
// 4 = 독
// 5 = 게이트
// 6 = 리버스
Stage::Stage() {
    for (int i = 0; i < MAP_SIZE ; i++)
        for (int j = 0; j < MAP_SIZE ; j++)
            map[i][j] = 0;

    for (int i = 0; i < MAP_SIZE; i++) {
        map[i][0] = 1;
        map[i][MAP_SIZE-1] = 1;
        map[MAP_SIZE-1][i] = 1;
        map[0][i] = 1;
    }
    map[0][0] = 2;
    map[MAP_SIZE-1][0] = 2;
    map[MAP_SIZE-1][MAP_SIZE-1] = 2;
    map[0][MAP_SIZE-1] = 2;
}

int Stage::getTileType(int x, int y) {
    return map[y][x];
}

void Stage::setTile(int x, int y, int type) {
    map[y][x] = type;

}

bool Stage::isGate(int x, int y) {
    return (map[y][x] == 5);
}

bool Stage::isPoison(int x, int y) {
    return (map[y][x] == 4);
}

bool Stage::isGrowth(int x, int y) {
    return (map[y][x] == 3);
}

bool Stage::isWall(int x, int y) {
    return (map[y][x] == 1);
}
bool Stage::isReverse(int x, int y) {
    return (map[y][x] == 6);
}