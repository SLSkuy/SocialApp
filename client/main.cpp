// 2023051604044 万睿
// 2024-12-23
// 社交软件主函数交互

#include "client.h"
#include "socialui.h"

#include <iostream>
using std::cin;     using std::cout;    using std::endl;    using std::cerr;
#include <string>
using std::string;
#include "thread"

int main()
{
    //启动客户端
    loadingAnimation();

    cout << "Welcome to Yuzu-ChatPlatform!\n";
    string serverIP;
    serverIP = getIP();
    cout <<  "Would you like to Sign-Up(1) or Log-In(2): ";

    int clientSocket;
    string userInput;
    while(cin >> userInput)
    {
        if(userInput == "1")
        {
            //signUp 本地输入账号密码等发送服务端
            clientSocket = connect2Server(serverIP);
            if(clientSocket < 0){    //尝试连接服务器
                //连接服务器失败程序退出
                return -1;
            }

            if(signUp(clientSocket)){
                //注册成功
                //启动用户交互界面
                cout << "signUp successfully" << endl;
                cout << "Enter\"/help\" to get help" << endl;
                break;
            }else{
                cout << "signUp failed: Duplicate name.\n"
                     << "The progress will exit." << endl;
                return -1;
            }
        }else if(userInput == "2"){
            clientSocket = connect2Server(serverIP);
            if (clientSocket < 0) { //尝试连接服务器
                //连接服务器失败程序退出
                return -1;
            }

            if (logIn(clientSocket)) {
                //注册成功
                //启动用户交互界面
                cout << "logIn successfully" << endl;
                cout << "Enter\"/help\" to get help" << endl;
                break;
            } else {
                cout << "logIn failed: No such user.\n"
                     << "The progress will exit." << endl;
                return -1;
            }
        } else {
            cout << "Please input 1 or 2, try again: ";
        }
    }

    std::thread(receiveFromServer,clientSocket).detach();   //创建新线程用于接受服务端发送信息
    sendMsg2Server(clientSocket);   //创建发送信息交互界面
    return 0;
}
