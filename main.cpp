// 2023051604044 万睿
// 2024-12-23
// 社交软件主函数交互

#include "socialui.h"
#include "server.h"
#include "dbcontrol.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

//TODO测试用
#include <vector>
#include "netizen.h"
std::vector<Netizen> netizens;
//测试用

int main()
{ /*
    cout << "Run in Client mode or Server mode (C/S): ";
    string userInput;
    while(cin >> userInput)
    {
        if(userInput == "S" or userInput == "s")
        {
            startServer();  //作为服务端
            break;
        }else if(userInput == "C" or userInput == "c"){
            startUp();  //作为用户端启动交互界面
            break;
        }else{
            cout << "Please input C or S: ";
        }
    }*/

    //TODO:测试函数
    DBControl db;
    db.initDB();
    db.loadNetizens(netizens);

    db.saveFriend("123", "456");
    db.delFriend("123", "456");
    //db.saveNetizen("123", "nick");
    //db.saveNetizen("456", "nick1");

    return 0;
}
