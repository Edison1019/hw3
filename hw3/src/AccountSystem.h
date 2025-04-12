#include <iostream>
#include <vector>
#include <utility>
#include "User.h"

class AccountSystem : private User {
    private:
        std::vector<User> user_list; // 所有使用者資料
        std::string login_user;
        std::string USER_DATA_PATH; // 使用者資料儲存位置
        void sign_up();
        void userdataUpdate();
    protected:
        void init(std::string USER_DATA_PATH);
        User* search(std::string name);
        std::pair<bool, std::string> login(); // 將兩個不同類型的值綁在一起
        void adding_user(std::string name, std::string password);
        std::string getuserLogin();
};