// 2023051604044 万睿
// 2024-12-23
// 社交软件主函数交互

#include "client.h"
#include "server.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

int main()
{
    cout << "Run in Client mode or Server mode (C/S): ";
    string userInput;
    while(cin >> userInput)
    {
        if(userInput == "S" or userInput == "s")
        {
            startServer();  //作为服务端
            break;
        }else if(userInput == "C" or userInput == "c"){
            // startUp();  //作为用户端启动交互界面
            break;
        }else{
            cout << "Please input C or S: ";
        }
    }

    return 0;
}
