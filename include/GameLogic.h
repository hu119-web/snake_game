#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include <random>
#include <conio.h>   // 用于键盘输入（Windows）
#include <windows.h> // 用于控制台控制（Windows）

// 方向枚举
enum Direction { UP, DOWN, LEFT, RIGHT };

// 坐标结构体
struct Point {
    int x;
    int y;
    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
};

class GameLogic {
private:
    std::vector<Point> snake;  // 蛇身
    Point food;                // 食物
    Direction dir;             // 当前方向
    int score;                 // 当前分数
    bool isGameOver;           // 游戏结束标志
    int width;                 // 游戏区域宽度
    int height;                // 游戏区域高度

    // 生成食物（避免生成在蛇身上）
    void generateFood();
    // 检查碰撞（边界/自身）
    bool checkCollision();
    // 移动蛇
    void moveSnake();

public:
    GameLogic(int w = 20, int h = 20);

    // 初始化游戏
    void initGame();
    // 处理用户输入
    void handleInput();
    // 游戏主循环一步
    bool update();
    // 获取当前分数
    int getScore() const;
    // 获取游戏结束状态
    bool getGameOver() const;
    // 获取蛇身
    std::vector<Point> getSnake() const;
    // 获取食物位置
    Point getFood() const;
    // 获取游戏区域尺寸
    int getWidth() const;
    int getHeight() const;
};

#endif // GAME_LOGIC_H