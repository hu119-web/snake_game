#include "../include/UserManager.h"
#include "../include/DataPersistence.h"
#include <fstream>
#include <iostream>

UserManager::UserManager() : currentUser(nullptr) {
    loadUsers();  // 初始化时加载所有用户数据
}

UserManager::~UserManager() {
    saveUsers();  // 析构时保存数据
}

bool UserManager::registerUser(const std::string& username, const std::string& password) {
    if (users.find(username) != users.end()) {
        return false;  // 用户名已存在
    }
    User newUser{username, password, 0};
    users[username] = newUser;
    saveUsers();
    return true;
}

bool UserManager::login(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if (it == users.end() || it->second.password != password) {
        return false;  // 用户名或密码错误
    }
    currentUser = &(it->second);
    return true;
}

void UserManager::logout() {
    currentUser = nullptr;
}

void UserManager::updateBestScore(int newScore) {
    if (currentUser && newScore > currentUser->bestScore) {
        currentUser->bestScore = newScore;
        saveUsers();
    }
}

User* UserManager::getCurrentUser() {
    return currentUser;
}

std::unordered_map<std::string, User> UserManager::getAllUsers() {
    return users;
}

void UserManager::loadUsers() {
    DataPersistence::loadUsersFromFile(users);
}

void UserManager::saveUsers() {
    DataPersistence::saveUsersToFile(users);
}