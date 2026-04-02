#include "../include/GameLogic.h"
#include <iostream>



GameLogic::GameLogic(int w, int h) : width(w), height(h), dir(RIGHT), score(0), isGameOver(false) {
    initGame();
}

void GameLogic::initGame() {
    snake.clear();
    // 初始化蛇身（3个节点）
    snake.push_back(Point(width/2, height/2));
    snake.push_back(Point(width/2 - 1, height/2));
    snake.push_back(Point(width/2 - 2, height/2));
    dir = RIGHT;
    score = 0;
    isGameOver = false;
    generateFood();
}

void GameLogic::generateFood() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> disX(0, width-1);
    std::uniform_int_distribution<int> disY(0, height-1);

    bool onSnake;
    do {
        onSnake = false;
        food.x = disX(gen);
        food.y = disY(gen);
        // 检查是否在蛇身上
        for (const auto& p : snake) {
            if (p.x == food.x && p.y == food.y) {
                onSnake = true;
                break;
            }
        }
    } while (onSnake);
}

bool GameLogic::checkCollision() {
    // 边界碰撞
    if (snake[0].x < 0 || snake[0].x >= width || snake[0].y < 0 || snake[0].y >= height) {
        return true;
    }
    // 自身碰撞
    for (size_t i = 1; i < snake.size(); ++i) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return true;
        }
    }
    return false;
}

void GameLogic::moveSnake() {
    // 新增头部（根据方向）
    Point newHead = snake[0];
    switch (dir) {
        case UP: newHead.y--; break;
        case DOWN: newHead.y++; break;
        case LEFT: newHead.x--; break;
        case RIGHT: newHead.x++; break;
    }
    snake.insert(snake.begin(), newHead);

    // 检查是否吃到食物
    if (newHead.x == food.x && newHead.y == food.y) {
        score += 10;  // 吃到食物加10分
        generateFood();
    } else {
        snake.pop_back();  // 没吃到食物则删除尾部
    }

    // 检查碰撞
    if (checkCollision()) {
        isGameOver = true;
    }
}

void GameLogic::handleInput() {
    if (_kbhit()) {  // 检测键盘输入
        switch (_getch()) {
            case 'w': case 'W': if (dir != DOWN) dir = UP; break;
            case 's': case 'S': if (dir != UP) dir = DOWN; break;
            case 'a': case 'A': if (dir != RIGHT) dir = LEFT; break;
            case 'd': case 'D': if (dir != LEFT) dir = RIGHT; break;
            case 'q': case 'Q': isGameOver = true; break;  // 按Q退出游戏
        }
    }
}

bool GameLogic::update() {
    if (!isGameOver) {
        handleInput();
        moveSnake();
    }
    return isGameOver;
}

int GameLogic::getScore() const {
    return score;
}

bool GameLogic::getGameOver() const {
    return isGameOver;
}

std::vector<Point> GameLogic::getSnake() const {
    return snake;
}

Point GameLogic::getFood() const {
    return food;
}

int GameLogic::getWidth() const {
    return width;
}

int GameLogic::getHeight() const {
    return height;
}