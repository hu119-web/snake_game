#ifndef DATA_PERSISTENCE_H
#define DATA_PERSISTENCE_H

#include <unordered_map>
#include <string>
#include "UserManager.h"

class DataPersistence {
public:
    // 保存用户数据到文件
    static void saveUsersToFile(const std::unordered_map<std::string, User>& users);
    // 从文件加载用户数据
    static void loadUsersFromFile(std::unordered_map<std::string, User>& users);

private:
    // 数据文件路径（固定）
    static const std::string DATA_FILE_PATH;
};

#endif // DATA_PERSISTENCE_H