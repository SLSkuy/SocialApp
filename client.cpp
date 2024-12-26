// 2023051604044 万睿
// 2024-12-25
// 客户端交互实现

#include "client.h"
#include "socialui.h"

#include <string>
using std::string;
#include <iostream>
using std::cin;     using std::cout;    using std::endl;    using std::cerr;
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
//#include <limits>
#include <cstring>

void startUp()
{
    //启动客户端
    loadingAnimation();

    cout << "Welcome to Yuzu-ChatPlatform!\n"
              <<  "Would you like to Sign-Up(1) or Log-In(2): ";

    int clientSocket;
    string userInput;
    while(cin >> userInput)
    {
        if(userInput == "1")
        {
            //signUp 本地输入账号密码等发送服务端
            clientSocket = connect2Server();
            if(clientSocket < 0){    //尝试连接服务器
                //连接服务器失败程序退出
                return;
            }

            if(signUp(clientSocket)){
                //注册成功
                //启动用户交互界面
                break;
            }else{
                cout << "signUp failed"
                     << "The progress will exit." << endl;
                return;
            }
        }else if(userInput == "2"){
            //logIn 输入账号密码等信息发送服务端检测
            break;
        }else{
            cout << "Please input 1 or 2, try again: ";
        }
    }

    std::thread(receiveFromServer,clientSocket).detach();   //创建新线程用于接受服务端发送信息
    sendMsg2Server(clientSocket);   //创建发送信息交互界面
}

bool signUp(int& clientSocket)
{
    return true;
}

int connect2Server()    //连接到服务器
{
    int clientSocket = socket(AF_INET,SOCK_STREAM,0);   //获取客户端socket
    if(clientSocket <= 0){
        cerr << "Socket creation failed!" << endl;
        return -1;
    }

    struct sockaddr_in serverAddress;   //服务器地址信息
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(8080);

    if(connect(clientSocket,(struct sockaddr*) &serverAddress,sizeof(serverAddress)) < 0){  //尝试连接服务器
        cout << "connect failed" << endl;
        return -1;
    }

    return clientSocket;
}

void sendMsg2Server(int& clientSocket)   //发送信息给服务端
{
    std::string buf;
    while (true) {
        buf.clear();

        //cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        cout << "Enter message: ";
        std::getline(cin,buf);

        // 发送消息到服务端
        send(clientSocket, buf.c_str(), 1024, 0);
    }
}

void receiveFromServer(int clientSocket)    //从服务端获取信息
{
    char buffer[1024];
    std::string buf;
    while(true){
        buf.clear();
        memset(buffer, 0, sizeof(buffer));
        int valread = recv(clientSocket, buffer, sizeof(buffer), 0);
        buf = buffer;

        if(valread <= 0)
        {
            cout << "Server is closed.\n"
                 << "The application will exit." << endl;
            exit(-1);
        }

        if(!buf.empty())
        {
            cout << "\033[2K\rreceive from server: " << buffer << endl;
            cout << "Enter message: " << std::flush;
        }
    }
}
