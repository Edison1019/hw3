#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include "AccountSystem.h"
#define red(text)    "\033[31m" text "\033[0m"
#define green(text)  "\033[32m" text "\033[0m"
#define yellow(text) "\033[33m" text "\033[0m"
#define blue(text)   "\033[34m" text "\033[0m"
#define magenta(text) "\033[35m" text "\033[0m"
#define cyan(text)   "\033[36m" text "\033[0m"
#define white(text)  "\033[37m" text "\033[0m"

User* AccountSystem::search(std::string name) { // 回傳User型別的指標
    for(size_t i=0;i<user_list.size();i++) {
        // do something 
        if(user_list[i].getUsername() == name)
            return &user_list[i];
    }
    return nullptr;
}
void AccountSystem::init(std::string USER_DATA_PATH) {
    AccountSystem::USER_DATA_PATH = USER_DATA_PATH;

    try {

        std::ifstream file(USER_DATA_PATH); // 讀檔
        if( !file ) {
            throw std::runtime_error("Error: File does not exist - " + USER_DATA_PATH);
        }

        // TODO: Loading user data from USER_DATA_PATH and call adding_user (from AccountSystem) function to insert data
        // Hints: stringstream

        std::string read_line;
        while( getline(file, read_line) ) { // 讀取一行
            std::string username, password;
            std::istringstream iss(read_line); // 把一整行當作字串流
            getline(iss, username, ','); // 以逗號分割，讀取逗號前的字串
            getline(iss, password); // 從逗號後開始讀          
            // do something
            
            AccountSystem::adding_user(username, password);
        }
        file.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }

}
void AccountSystem::sign_up() {
    std::string name;
    std::string passwd1, passwd2;
    std::cout<<yellow("Welcome! please enter your name");
    std::cin>>name;
    while(1){
        std::cout<<yellow("Please enter your password");
        std::cin>>passwd1;
        std::cout<<yellow("Please enter your password again");
        std::cin>>passwd2;
        if(passwd1 != passwd2)
            std::cout<<red("two passwords are not not the same, please try again")<<"\n";
        else
            break;
    }
    AccountSystem::adding_user(name, passwd2);
    AccountSystem::login();
}
std::pair<bool, std::string> AccountSystem::login() {
    std::pair<bool, std::string> result = std::make_pair(false, "");
    std::string name;
    std::string passwd;
    int cnt = 0;
    while(1){
        std::cout<<yellow("User Name (Enter -1 to sign up): ");
        std::cin>>name;
        if(name == "-1"){
            AccountSystem::sign_up();
            return result;
        }
        if(AccountSystem::search(name) == nullptr){
            std::cout<<red("User is not exit!")<<"\n";
        }
        else{
            std::cout<<"Welcome abord, "<<name<<"\n";
            std::cout<<"Please enter your passsword: ";
            while(std::cin>>passwd){
                if(AccountSystem::search(name)->getPassword() == passwd){
                    AccountSystem::login_user = name;
                    result.first = true;
                    result.second = name;
                    std::cout<<"\n"<<green("Login Success!!! welcome aborad")<<"\n";
                    return result;
                }
                else{
                    std::cout<<red("Password incorrect... please try again")<<"\n";
                    cnt++;
                    if(cnt == 3){
                        std::cout<<red("Too many unseccessful aign-in attempts")<<"\n";
                        break;
                    }
                }
            }

        }
    }    

}
void AccountSystem::adding_user(std::string username, std::string password) {
    User new_user(username, password);
    user_list.push_back(new_user);
    AccountSystem::userdataUpdate();
    return;
}
std::string AccountSystem::getuserLogin() {
    return AccountSystem::login_user;
}
void AccountSystem::userdataUpdate() {
    try {
        std::ofstream info_out(AccountSystem::USER_DATA_PATH); // 寫檔，把資料寫進 "USER_DATA_PATH"
        if( !info_out ) {
            throw std::runtime_error("Error: File does not exist - " + USER_DATA_PATH);
        }

        // 把整個 vector 跑過一次，透過 info_out 寫入
        // Hints: 你可能會需要 class User 的 getter 才能取得某些資訊
        for(size_t i=0; i<user_list.size(); i++){
            info_out<<user_list[i].getUsername()<<","<<user_list[i].getPassword()<<"\n";
        }

        info_out.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }    

}