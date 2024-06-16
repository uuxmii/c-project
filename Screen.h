
#ifndef SNAKEGAME_SCREEN_H
#define SNAKEGAME_SCREEN_H
#define SCREEN_SIZE 21

#include "Snake.h"
#include "Mission.h"
#include "Stage.h"

class Screen {
    void drawBox(int x, int y, int height, int width);
    void drawBlock(int x, int y);
    void clearBlock(int x, int y);
    void drawSnake();
public:
    Snake *snake;
    Stage *stage;
    Mission *mission;
    int *current;
    Screen();
    void setSnake(Snake &snake);
    void setStage(Stage &stage);
    void update();
    void GameOver();

    void GameEnd();

    void setMission(Mission &mission);

    void setCurrentStage(int &current);
};


#endif //SNAKEGAME_SCREEN_H
