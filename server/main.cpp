// 2023051604044 万睿
// 2024-12-23
// 社交软件主函数交互

#include "server.h"

#include <iostream>
using std::cin;     using std::cout;    using std::endl;    using std::cerr;

int main()
{
    //启动服务端
    cout << "Specify a specific access IP address? (Y/N): ";
    std::string input,accessIP;
    while(cin >> input){
        if(input == "Y" or input == "y"){
            cout << "Please input IP address: ";
            cin >> accessIP;
            break;
        }else if(input == "N" or input == "n"){
            accessIP = "0.0.0.0";
            break;
        }else{
            cout << "Please input Y or N, try again: ";
        }
    }

    cout << "Input listening port(enter default to use default value): ";
    std::string port;
    if(cin >> port){
        if(port == "default")port = "8080";
    }else{
        cout << "Input port failed" << endl;
        return -1;
    }

    cout << "The Server is loading..." << endl;
    //创建服务器对象
    Server server(accessIP,port);
    server.initServer();    //初始化服务端

    server.handleClientSocket();   //捕获客户端请求

    return 0;
}
