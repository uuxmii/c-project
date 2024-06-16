

#include "Screen.h"
#include "ncurses.h"
using namespace std;

Screen::Screen() {
    initscr();
    noecho();
    refresh();
}
void Screen::drawBox(int x, int y, int height, int width) {
    width = width*2;
    int i,j;
    move(y,x);
    addch(ACS_ULCORNER);
    for(i=0;i<width;i++)
        addch(ACS_HLINE);
    addch(ACS_URCORNER);
    for(j=0;j<height;j++){
        move(y+j+1,x);
        addch(ACS_VLINE);
        move(y+j+1,x+width+1);
        addch(ACS_VLINE);
    }
    move(y+j+1,x);
    addch(ACS_LLCORNER);
    for(i=0;i<width;i++)
        addch(ACS_HLINE);
    addch(ACS_LRCORNER);
}


void Screen::drawBlock(int x, int y) {
    move(y+1,x*2+1);
    attron(A_REVERSE);
    attron(COLOR_PAIR(2));
    printw("  ");
    attroff(A_REVERSE);
}
void Screen::clearBlock(int x, int y) {
    move(y+1,x*2+1);
    attron(COLOR_PAIR(2));
    printw("  ");
}

void Screen::drawSnake() {
    for (auto i : snake->body) {
//        drawBlock(i.first, i.second);
        move(i.second, i.first*2);
        printw("O");
    }
}

void Screen::setSnake(Snake &snake) {
    this->snake = &snake;
}

void Screen::setStage(Stage &stage) {
    this->stage = &stage;
}
void Screen::setMission(Mission &mission) {
    this->mission = &mission;
}

void Screen::update() {
    for (int i = 0; i < 21; i++)
        for (int j = 0; j < 21 ; j++) {
            move(i,j*2);
            switch (stage->getTileType(j, i)) {
                case 0:
                    printw("  ");
                    break;
                case 1: // 벽
                    attron(A_REVERSE);
                    printw("  ");
                    attroff(A_REVERSE);
                    break;
                case 2: // 코너
                    attron(A_REVERSE);
                    printw("  ");
                    attroff(A_REVERSE);
                    break;
                case 3:
                    printw("+ ");
                    break;
                case 4:
                    printw("- ");
                    break;
                case 5:
                    printw("@@");
                    break;
                case 6:
                    printw("R");
                    break;
                default:
                    break;
            }

        }
    drawSnake();
    drawBox(47, 1, 1, 10);
    move(2, 52);
    printw("GAME STAGE %d", 1+*current);
    drawBox(47, 5, 5, 10);
    drawBox(47, 13, 5, 10);

    move(5, 49);
    printw("SCORE BOARD");
    move(6, 50);
    printw(" B: %d / %d", snake->length, snake->max_length);
    move(7, 50);
    printw(" +: %d", snake->growth_count);
    move(8, 50);
    printw(" -: %d", snake->poison_count);
    move(9, 50);
    printw(" G: %d", snake->gate_count);
    move(10, 50);
    printw(" R: %d", snake->reverse_count);

    move(13, 49);
    printw("STAGE MISSION");
    move(14, 50);
    printw(" B: %d (%c)", mission->length, snake->max_length >= mission->length ? 'v' : ' ' );
    move(15, 50);
    printw(" +: %d (%c)", mission->growth_count, snake->growth_count >= mission->growth_count ? 'v' : ' ');
    move(16, 50);
    printw(" -: %d (%c)", mission->poison_count, snake->poison_count >= mission->poison_count ? 'v' : ' ');
    move(17, 50);
    printw(" G: %d (%c)", mission->gate_count, snake->gate_count >= mission->gate_count ? 'v' : ' ');
    move(18, 50);
    printw(" R: %d (%c)", mission->reverse_count,snake->reverse_count >= mission->reverse_count ? 'v' : ' ' );
    move(22,0);


    refresh();
}

void Screen::GameOver() {
    move(11, 15);
    attron(A_REVERSE);
    printw("Game Over!");
    attroff(A_REVERSE);
    move(22,0);
    refresh();

}
void Screen::GameEnd() {
    move(11, 15);
    attron(A_REVERSE);
    printw("You Win!");
    attroff(A_REVERSE);
    move(22,0);
    refresh();

}

void Screen::setCurrentStage(int &current) {
    this->current = &current;
}
