#include "../include/DataPersistence.h"
#include <fstream>
#include <iostream>

const std::string DataPersistence::DATA_FILE_PATH = "data/users.dat";

void DataPersistence::saveUsersToFile(const std::unordered_map<std::string, User>& users) {
    std::ofstream file(DATA_FILE_PATH, std::ios::binary | std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "无法打开数据文件进行保存！" << std::endl;
        return;
    }

    // 先写入用户数量
    size_t userCount = users.size();
    file.write(reinterpret_cast<const char*>(&userCount), sizeof(userCount));

    // 逐个写入用户数据
    for (const auto& pair : users) {
        const User& user = pair.second;
        // 写入用户名（长度+内容）
        size_t nameLen = user.username.size();
        file.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
        file.write(user.username.c_str(), nameLen);
        // 写入密码（长度+内容）
        size_t pwdLen = user.password.size();
        file.write(reinterpret_cast<const char*>(&pwdLen), sizeof(pwdLen));
        file.write(user.password.c_str(), pwdLen);
        // 写入最高分
        file.write(reinterpret_cast<const char*>(&user.bestScore), sizeof(user.bestScore));
    }

    file.close();
}

void DataPersistence::loadUsersFromFile(std::unordered_map<std::string, User>& users) {
    std::ifstream file(DATA_FILE_PATH, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "首次运行，创建新数据文件！" << std::endl;
        return;
    }

    // 读取用户数量
    size_t userCount;
    file.read(reinterpret_cast<char*>(&userCount), sizeof(userCount));

    // 逐个读取用户数据
    for (size_t i = 0; i < userCount; ++i) {
        User user;
        // 读取用户名
        size_t nameLen;
        file.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        user.username.resize(nameLen);
        file.read(&user.username[0], nameLen);
        // 读取密码
        size_t pwdLen;
        file.read(reinterpret_cast<char*>(&pwdLen), sizeof(pwdLen));
        user.password.resize(pwdLen);
        file.read(&user.password[0], pwdLen);
        // 读取最高分
        file.read(reinterpret_cast<char*>(&user.bestScore), sizeof(user.bestScore));

        users[user.username] = user;
    }

    file.close();
}