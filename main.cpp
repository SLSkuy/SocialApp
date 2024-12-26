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

//测试用
#include <vector>
#include "netizen.h"
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
    DBControl db;
    db.initDB();
    std::vector<Netizen> netizens;
    db.loadNetizens(netizens);
    Netizen netizen{"123", "nick"};
    db.saveNetizen(netizen);

    std::cout << "1";
    /*mysqlpp::Connection connection;

    mysqlpp::Query query = connection.query();
    query << "Select * From Netizens";
    mysqlpp::StoreQueryResult result = query.store();
    for (int i = 0; i != result.num_rows(); i++) {
        for (int j = 0; j != result[i].size(); j++) {
            std::cout << result[i][j] << " ";
        }
        cout << std::endl;
    }*/

    return 0;
}
