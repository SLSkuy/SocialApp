// 2023051604044 万睿
// 2024-12-23
// 软件ui交互实现

#include "socialui.h"

#include <iostream>
#include <string>

void startUp()
{
    //启动客户端
    std::cout << "Welcome to Yuzu-ChatPlatform!\n"
         <<  "Would you like to sign up(1) or log in(2): ";
    std::string userInput;
    while(std::cin >> userInput)
    {
        if(userInput == "1")
        {
            //signUp
            break;
        }else if(userInput == "2"){
            //logIn
            break;
        }else{
            std::cout << "Please input 1 or 2, try again: ";
        }
    }
}
