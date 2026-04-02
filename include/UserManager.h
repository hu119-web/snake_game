#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <unordered_map>

// 用户信息结构体
struct User {
    std::string username;
    std::string password;
    int bestScore;          // 历史最高分
};

class UserManager {
private:
    std::unordered_map<std::string, User> users;  // 所有用户数据
    User* currentUser;                            // 当前登录用户

    // 加载用户数据（内部调用）
    void loadUsers();
    // 保存用户数据（内部调用）
    void saveUsers();

public:
    UserManager();
    ~UserManager();

    // 注册账号
    bool registerUser(const std::string& username, const std::string& password);
    // 登录账号
    bool login(const std::string& username, const std::string& password);
    // 退出登录
    void logout();
    // 更新当前用户最高分
    void updateBestScore(int newScore);
    // 获取当前登录用户
    User* getCurrentUser();
    // 获取所有用户（用于排行榜）
    std::unordered_map<std::string, User> getAllUsers();
};

#endif // USER_MANAGER_H