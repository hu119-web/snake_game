#include "../include/UI.h"
#include <iostream>
#include <vector>
#include <algorithm>
// 移除不需要的 <chrono> 和 <thread>
#include <windows.h>  // Sleep() 依赖此头文件

UI::UI(UserManager& um) : userManager(um), game(30, 20) {}

void UI::clearScreen() {
    // Windows清屏
    system("cls");
    // Linux/Mac可替换为：system("clear");
}

void UI::setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void UI::drawGame() {
    clearScreen();
    int width = game.getWidth();
    int height = game.getHeight();

    // 绘制上边界
    std::cout << "+";
    for (int i = 0; i < width; ++i) std::cout << "-";
    std::cout << "+" << std::endl;

    // 绘制游戏区域
    for (int y = 0; y < height; ++y) {
        std::cout << "|";
        for (int x = 0; x < width; ++x) {
            bool isSnake = false;
            // 检查是否是蛇身
            for (const auto& p : game.getSnake()) {
                if (p.x == x && p.y == y) {
                    std::cout << "O";
                    isSnake = true;
                    break;
                }
            }
            // 检查是否是食物
            if (!isSnake && game.getFood().x == x && game.getFood().y == y) {
                std::cout << "*";
            } else if (!isSnake) {
                std::cout << " ";
            }
        }
        std::cout << "|" << std::endl;
    }

    // 绘制下边界
    std::cout << "+";
    for (int i = 0; i < width; ++i) std::cout << "-";
    std::cout << "+" << std::endl;

    // 显示信息
    User* currentUser = userManager.getCurrentUser();
    std::cout << "当前用户：" << currentUser->username << std::endl;
    std::cout << "当前分数：" << game.getScore() << " | 历史最高分：" << currentUser->bestScore << std::endl;
    std::cout << "操作：W(上) S(下) A(左) D(右) | Q(退出游戏)" << std::endl;
}

void UI::showRanking() {
    clearScreen();
    std::cout << "==================== 成绩排行榜 ====================" << std::endl;
    auto users = userManager.getAllUsers();
    // 转换为vector并按最高分排序
    std::vector<User> userList;
    for (const auto& pair : users) {
        userList.push_back(pair.second);
    }
    std::sort(userList.begin(), userList.end(), [](const User& a, const User& b) {
        return a.bestScore > b.bestScore;
    });

    // 显示排行榜
    int rank = 1;
    for (const auto& user : userList) {
        std::cout << rank << ". " << user.username << " - " << user.bestScore << "分" << std::endl;
        rank++;
    }

    std::cout << "\n按任意键返回主菜单..." << std::endl;
    _getch();
}

void UI::showMainMenu() {
    clearScreen();
    std::cout << "==================== 贪吃蛇游戏 ====================" << std::endl;
    std::cout << "当前登录：" << userManager.getCurrentUser()->username << std::endl;
    std::cout << "1. 开始游戏" << std::endl;
    std::cout << "2. 查看排行榜" << std::endl;
    std::cout << "3. 退出登录" << std::endl;
    std::cout << "请选择操作（1-3）：";
}

bool UI::loginOrRegister() {
    clearScreen();
    std::cout << "==================== 登录/注册 ====================" << std::endl;
    std::cout << "1. 登录账号" << std::endl;
    std::cout << "2. 注册账号" << std::endl;
    std::cout << "请选择（1/2）：";
    char choice;
    std::cin >> choice;

    std::string username, password;
    std::cout << "用户名：";
    std::cin >> username;
    std::cout << "密码：";
    std::cin >> password;

    if (choice == '1') {
        if (userManager.login(username, password)) {
            std::cout << "登录成功！按任意键进入主菜单..." << std::endl;
            _getch();
            return true;
        } else {
            std::cout << "用户名或密码错误！按任意键重试..." << std::endl;
            _getch();
            return false;
        }
    } else if (choice == '2') {
        if (userManager.registerUser(username, password)) {
            std::cout << "注册成功！自动登录中..." << std::endl;
            userManager.login(username, password);
            Sleep(1000);  // 替换 std::this_thread::sleep_for
            return true;
        } else {
            std::cout << "用户名已存在！按任意键重试..." << std::endl;
            _getch();
            return false;
        }
    } else {
        std::cout << "输入错误！按任意键重试..." << std::endl;
        _getch();
        return false;
    }
}

void UI::gameLoop() {
    game.initGame();
    while (!game.update()) {
        drawGame();
        Sleep(150);  // 替换 std::this_thread::sleep_for
    }

    // 游戏结束，更新最高分
    int finalScore = game.getScore();
    userManager.updateBestScore(finalScore);
    clearScreen();
    std::cout << "游戏结束！最终分数：" << finalScore << std::endl;
    std::cout << "历史最高分：" << userManager.getCurrentUser()->bestScore << std::endl;
    std::cout << "按任意键返回主菜单..." << std::endl;
    _getch();
}

void UI::start() {
    // 登录/注册流程
    while (!loginOrRegister());

    // 主菜单循环
    while (true) {
        showMainMenu();
        char choice;
        std::cin >> choice;
        switch (choice) {
            case '1':
                gameLoop();
                break;
            case '2':
                showRanking();
                break;
            case '3':
                userManager.logout();
                std::cout << "已退出登录！" << std::endl;
                return;
            default:
                std::cout << "输入错误！按任意键重试..." << std::endl;
                _getch();
                break;
        }
    }
}