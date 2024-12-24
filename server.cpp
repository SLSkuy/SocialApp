// 2023051604044 万睿
// 2024-12-23
// 网络聊天实现

#include "server.h"

#include <iostream>
using std::cin;     using std::cout;    using std::endl;    using std::cerr;
#include <string>
#include <thread>
#include <sys/socket.h>  //socket套接字
#include <arpa/inet.h>  //网络传输格式转换
#include <cstring>  //memset

void startServer()
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
        return;
    }

    cout << "The Server is loading..." << endl;
    //创建服务器对象
    Server server(accessIP,port);

    server.handleClientSocket(server.m_serverSocket);
}

void Server::initServer()   //初始化获取服务端socket
{
    //创建socket套接字
    int serverFd = socket(AF_INET, SOCK_STREAM, 0); //Ipv4协议，传输流, 不使用保护协议
    if(serverFd <= 0){
        cerr << "Socket creation failed!" << endl;
        return;
    }

    //绑定端口号
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;     //Ipv4协议
    serverAddress.sin_addr.s_addr = inet_addr(m_IP.c_str());    //转换为大端字节序列
    serverAddress.sin_port = htons(stoi(m_Port));  //转换为大端字节序列适应于网络传输

    if(bind(serverFd,(struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0)
    {
        cerr << "Socket bind failed!" << endl;
        return;
    }

    //监听端口
    if(listen(serverFd,0) < 0)  //最多0个排队请求
    {
        cerr << "listen failed on port " << m_Port << endl;
        return;
    }

    cout << "Server initialization completed.\n"
         << "Server is listening on port " << m_Port << "..." << endl;

    m_serverSocket = serverFd;
}

void Server::handleClientSocket(int serverSocket)
{
    while(true){
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);  // 初始化地址结构大小
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);

        if(clientSocket < 0)
        {
            cerr << "Accept failed!" << endl;
            return;
        }

        int clientPort{ntohs(clientAddress.sin_port)};
        cout << "Client on " << clientPort << " connected." << endl;
        std::thread(&Server::handleClientMessage,this,clientSocket, clientPort).detach();
    }
}

void Server::handleClientMessage(int clientSocket, int port) {
    char buffer[1024];
    int valread;

    while (true) {
        memset(buffer, 0, sizeof(buffer));  //刷新缓存区域防止残留信息
        valread = recv(clientSocket, buffer, sizeof(buffer),0);
        if (valread <= 0) {
            std::cerr << "Client disconnected" << std::endl;
            close(clientSocket);
            break;
        }

        std::cout << "Message from client(Port: " << port << "): " << buffer << std::endl;
    }
}
