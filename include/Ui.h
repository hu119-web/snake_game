#ifndef UI_H
#define UI_H

#include "UserManager.h"
#include "GameLogic.h"

class UI {
private:
    UserManager& userManager;  // 引用用户管理模块
    GameLogic game;            // 游戏逻辑实例

    // 清屏（跨平台兼容）
    void clearScreen();
    // 设置控制台光标位置
    void setCursorPosition(int x, int y);
    // 绘制游戏界面
    void drawGame();
    // 显示排行榜
    void showRanking();
    // 显示主菜单
    void showMainMenu();
    // 登录/注册界面
    bool loginOrRegister();
    // 游戏主循环
    void gameLoop();

public:
    UI(UserManager& um);
    // 启动UI（程序入口）
    void start();
};

#endif // UI_H