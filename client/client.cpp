// 2023051604044 万睿
// 2024-12-25
// 客户端交互实现

#include "client.h"
#include "socialui.h"

#include <sys/socket.h>
#include <arpa/inet.h>
//#include <limits>
#include <cstring>
#include <string>
using std::string;
#include <iostream>
using std::cin;     using std::cout;    using std::endl;    using std::cerr;
#include <thread>

bool signUp(int& clientSocket)
{
    string input;
    cout << "Please enter your name: ";
    cin >> input;
    string buf{"/signUp " + input};
    send(clientSocket,buf.c_str(),buf.size(),0);

    char buffer[128];
    memset(buffer,0,128);
    recv(clientSocket,buffer,128,0);
    buf = buffer;
    if(buf == "failed")return false;
    return true;
}

bool logIn(int& clientSocket)
{
    string input;
    cout << "Please enter your name: ";
    cin >> input;
    string buf{"/logIn " + input};
    send(clientSocket, buf.c_str(), buf.size(), 0);

    char buffer[128];
    memset(buffer, 0, 128);
    recv(clientSocket, buffer, 128, 0);
    buf = buffer;
    if (buf == "failed") return false;
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

        cout << "Enter message: ";
        //cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::getline(cin,buf);
        if (buf == "/help") {
            cout << "/friend <name>       Add friend." << endl;
            cout << "/del <name>          Delete friend." << endl;
            cout << "/m <name> <content>  Private chat." << endl;
            cout << "/list                List friends." << endl;
        }
        // 发送消息到服务端
        else
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
            //cout << "\033[2K\rreceive from server: " << buf << endl;
            cout << "\033[2K\r" << buf << endl;
            cout << "Enter message: " << std::flush;
        }
    }
}
