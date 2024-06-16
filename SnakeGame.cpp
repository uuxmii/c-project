
#include "SnakeGame.h"
#include "ncurses.h"
#include <ctime>
#include <cmath>
#include <cstdlib>
using namespace std;

SnakeGame::SnakeGame() {
    srand((unsigned int)time(NULL));
    current = 0;
    mission[0] = Mission(5, 1, 2, 1, 1);
    mission[1] = Mission(7, 2, 3, 2, 2);
    mission[2] = Mission(9, 3, 4, 2, 3);
    mission[3] = Mission(11, 4, 5, 3, 4);
    // 스테이지 2의 맵 에는 중앙에 갈 선이 있음
    for (int i = 0 ; i < 10 ; i++)
        stage[1].setTile(5+i, 6, 1);

    // 스테이지 3의 맵에는 중앙에 ㄴ ㄱ 모양이 존재함
    for (int i = 0 ; i < 5 ; i++) {
        stage[2].setTile(0+i, 4, 1);
        stage[2].setTile(4, 4+i, 1);
        stage[2].setTile(16+i, 16, 1);
        stage[2].setTile(16, 16-i, 1);
    }

    // 스테이지 4 X 자 맵
    for (int i =0; i < 5 ; i++) {
        stage[3].setTile(0+i, 0+i, 1);
        stage[3].setTile(4-i, 0+i, 1);
        stage[3].setTile(16+i, 16+i, 1);
        stage[3].setTile(20-i, 16+i, 1);
        stage[3].setTile(0+i, 16+i, 1);
        stage[3].setTile(4-i, 16+i, 1);
        stage[3].setTile(16+i, 0+i, 1);
        stage[3].setTile(20-i, 0+i, 1);
    }


    screen.setSnake(snake);
    screen.setStage(stage[current]);
    screen.setCurrentStage(current);
    screen.setMission(mission[current]);

    noecho();
    nodelay(stdscr, true);

}

void SnakeGame::start() {
    clock_t last_move, item_spawn_time, gate_spawn_time;
    last_move = item_spawn_time = gate_spawn_time = clock();
    while (true) {
        // 현재 미션이 is_complete 함수를 통하여 내 뱀이 현재 스테이지가 요구하는 미션 기준을 달성하였는지 체크
        if (mission[current].is_complete(snake)) {
            if (current == 3) {
                screen.GameEnd();
                break;
            }
            current++;
            screen.setStage(stage[current]);
            screen.setMission(mission[current]);
            snake = Snake();
            last_move = item_spawn_time = gate_spawn_time = clock();
        }
        double duration;
        duration = (double)(clock() - last_move) / CLOCKS_PER_SEC;

        if (duration >= 0.3) {
            snake.move();
            int x = snake.body.front().first;
            int y = snake.body.front().second;
            if (stage[current].isPoison(x, y)){
                snake.poison();
                stage[current].setTile(x, y, 0);
            }
            if (stage[current].isGrowth(x, y)) {
                snake.growth();
                stage[current].setTile(x, y, 0);
            }
            if (stage[current].isWall(x, y) || snake.isDead()) {
                screen.update();
                screen.GameOver();
                break;
            }
            if(stage[current].isReverse(x, y)) {
                snake.reverse();
                stage[current].setTile(x, y, 0);
            }


            // 게이트에 접촉했다면
            if(stage[current].isGate(x, y)) {
                snake.gate_count++;
                // 방향을 숫자로 변환 90도 180도 270도 360도를 간편히 0 1 2 3 표현함.
                int direction_number;
                if (snake.direction == 'w')
                    direction_number = 0;
                else if (snake.direction == 'a')
                    direction_number = 1;
                else if (snake.direction == 's')
                    direction_number = 2;
                else if (snake.direction == 'd')
                    direction_number = 3;

                // 각도를 x y 변화량으로 변환 해주는 배열 생성
                int convert_to_xy_diff[4][2] = {{0, -1},{-1, 0},{0, 1}, {1, 0}};

                Gate otherGate;
                // 지금 위치가 Gate A의 위치 인가?
                if (gateA.gate_x == x && gateA.gate_y == y)
                    otherGate = gateB;
                else
                    otherGate = gateA;

                for (int i = 0; i < 4; i++) {
                    direction_number = direction_number+i - floor( (direction_number+i) / 4)*4;
                    if (stage[current]
                                .getTileType(otherGate.gate_x +convert_to_xy_diff[direction_number][0],
                                             otherGate.gate_y +convert_to_xy_diff[direction_number][1]) == 0) {
                        snake.body.insert(snake.body.begin(), {otherGate.gate_x +convert_to_xy_diff[direction_number][0],
                                                               otherGate.gate_y +convert_to_xy_diff[direction_number][1]});

                        char number_to_direction[4] = {'w', 'a', 's','d'};
                        snake.direction = number_to_direction[direction_number];
                        break;
                    }
                }
            }


            last_move = clock();
            screen.update();
        }
        //아이템 스폰 이벤트
        duration = (double)(clock() - item_spawn_time) / CLOCKS_PER_SEC;
        if (duration >= 5.0){

            // 기존에 존재하는 아이템 모두 공기로 변경
            for (int i = 0; i < 21; i++)
                for (int j = 0; j < 21; j++) {
                    if (stage[current].getTileType(i, j) == 5) break;
                    if (stage[current].getTileType(i, j) > 2) stage[current].setTile(i, j, 0);
                }

            // 아이템을 3개 만큼 생성
            for (int count = 0; count < 3 ; count ++) {

                // 남은 공기 개수를 구함.
                int air_count = 0;
                for (int i = 0; i < 21; i++)
                    for (int j = 0; j < 21; j++)
                        if (stage[current].getTileType(i, j) == 0) air_count++;

                // 남은 공기 개수 중 몇번째 자리의 공기를 아이템으로 변경할 것인지 임의로 고름.
                int rand_loc = rand() % air_count;
                int r_x, r_y;
                air_count = 0;
                for (int i = 0; i < 21; i++)
                    for (int j = 0; j < 21; j++)
                        if (stage[current].getTileType(i, j) == 0) {
                            air_count++;
                            if (air_count == rand_loc) {
                                r_x = i;
                                r_y = j;
                            }
                        }


                // 선택된 공기 자리를 어떤 아이템으로 바꿀 것인지 임의로 구함.
                switch (rand() % 3) {
                    case 0: //독
                        stage[current].setTile(r_x, r_y, 4);
                        break;
                    case 1: //사과
                        stage[current].setTile(r_x, r_y, 3);
                        break;
                    case 2: // 리버스
                        stage[current].setTile(r_x, r_y, 6);
                        break;
                }
                item_spawn_time = clock();

            }
        }


        // 게이트 랜덤 스폰
        duration = (double)(clock() - gate_spawn_time) / CLOCKS_PER_SEC;
        if (duration >= 10.0) {

            // 만약 뱀이 게이트를 이용 중인지 판단
            // 게이트를 이용 중이라면 몸과 몸 사이의 거리가 1을 초과하는 것이 존재해야 함
            int b_x = snake.body.front().first;
            int b_y = snake.body.front().second;
            bool using_gate = false;
            for (int i = 1; i < snake.body.size(); i++){
                if ((b_x - snake.body[i].first) * (b_x - snake.body[i].first) +
                    (b_y - snake.body[i].second) * (b_y - snake.body[i].second ) > 1)
                    using_gate = true;
                b_x = snake.body[i].first;
                b_y = snake.body[i].second;
            }
            // 게이트를 이용 중이지 않는다면
            if (!using_gate) {
                // 기존에 존재하는 게이트를 벽으로 변경
                for (int i = 0; i < 21; i++)
                    for (int j = 0; j < 21; j++) {
                        if (stage[current].getTileType(i, j) == 5) stage[current].setTile(i, j, 1);
                    }

                // 벽 타일 개수를 구함.
                int wall_count = 0;
                for (int i = 0; i < 21; i++)
                    for (int j = 0; j < 21; j++)
                        if (stage[current].getTileType(i, j) == 1) wall_count++;

                // 임의의 벽을 선정 후 게이트로 변경
                int wall_random = rand() % wall_count;
                wall_count = 0;
                for (int i = 0; i < 21; i++)
                    for (int j = 0; j < 21; j++)
                        if (stage[current].getTileType(i, j) == 1) {
                            wall_count++;
                            if (wall_count == wall_random) {
                                stage[current].setTile(i, j, 5);
                                gateA = Gate(i, j);
                            }
                        }

                // 벽 타일 개수를 구함.
                wall_count = 0;
                for (int i = 0; i < 21; i++)
                    for (int j = 0; j < 21; j++)
                        if (stage[current].getTileType(i, j) == 1) wall_count++;

                // 임의의 벽을 선정 후 게이트로 변경
                wall_random = rand() % wall_count;
                wall_count = 0;
                for (int i = 0; i < 21; i++)
                    for (int j = 0; j < 21; j++)
                        if (stage[current].getTileType(i, j) == 1) {
                            wall_count++;
                            if (wall_count == wall_random) {
                                stage[current].setTile(i, j, 5);
                                gateB = Gate(i, j);
                            }
                        }
                gate_spawn_time = clock();

            }
        }
    }
}
