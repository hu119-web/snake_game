#include "../include/UserManager.h"
#include "../include/UI.h"
#include <iostream>

int main() {
    // 设置控制台编码（解决中文乱码，Windows）
    SetConsoleOutputCP(CP_UTF8);

    // 初始化核心模块
    UserManager userManager;
    UI ui(userManager);

    // 启动游戏
    ui.start();

    return 0;
}