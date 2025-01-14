// 2023051604044 万睿
// 2024-12-23
// 服务端启动相关

#include "server.h"

#include <sys/socket.h>  //socket套接字
#include <arpa/inet.h>  //网络传输格式转换
#include <cstring>  //memset
#include <iostream>
using std::cin;     using std::cout;    using std::endl;    using std::cerr;
#include <string>
#include <thread>
#include <sstream>

void Server::initServer()   //初始化获取服务端socket
{
    //创建socket套接字
    int serverFd = socket(AF_INET, SOCK_STREAM, 0); //Ipv4协议，传输流, 不使用保护协议
    if(serverFd <= 0){
        cerr << "Socket creation failed!" << endl;
        return;
    }


    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;     //Ipv4协议
    serverAddress.sin_addr.s_addr = inet_addr(m_IP.c_str());    //转换为大端字节序列
    serverAddress.sin_port = htons(stoi(m_Port));  //转换为大端字节序列适应于网络传输

    //绑定端口号
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

    //数据库
    if (!m_db.initDB()) return;
    if (!m_db.loadNetizens(m_netizens)) return;

    cout << "Server initialization completed.\n"
         << "Server is listening on port " << m_Port << "..." << endl;

    m_serverSocket = serverFd;
}

void Server::handleClientSocket()   //捕获客户端socket
{
    int serverSocket{m_serverSocket};
    while(true){
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);  // 初始化地址结构大小
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);

        if(clientSocket < 0)
        {
            cerr << "Accept failed!" << endl;
            return;
        }else{
            int clientPort{ntohs(clientAddress.sin_port)};
            cout << "Client on port " << clientPort << " connected." << endl;

            cerr << "clientPort:" << clientPort << " clientSocket:" << clientSocket << endl;
            m_sockets[clientPort] = clientSocket;

            std::thread(&Server::handleClientMessage,this,clientSocket, clientPort).detach();   //每成功捕获一个用户连接新开一个线程用于接受客户端消息
        }
    }
}

void Server::handleClientMessage(int clientSocket, int clientPort)  //捕获客户端信息
{
    char buffer[1024];
    std::string buf;

    while (true) {
        buf.clear();
        memset(buffer, 0, sizeof(buffer));  //刷新缓存区域防止残留信息
        int valread = recv(clientSocket, buffer, sizeof(buffer),0);
        buf = buffer;

        if (valread <= 0) { //未接收到消息
            std::cerr << "Client disconnected" << std::endl;
            m_sockets.erase(clientPort);
            m_clients.erase(clientPort);
            close(clientSocket);
            break;
        }else{
            if(!buf.empty())
            {
                std::cout << "Message from client(Port: " << clientPort << "): " << buf << std::endl; //屏蔽空消息
                clientProcess(buf,clientPort);
            }
        }
    }
}

bool Server::regNetizen(std::string nickName,int clientSocket,int clientPort)
{
    for(auto& it : m_netizens){
        if(it.getName() == nickName)return false;
    }
    Netizen newUser(nickName,clientSocket,this);
    m_netizens.emplace_back(newUser);
    m_clients[clientPort] = nickName;
    m_sockets[clientPort] = clientSocket;
    m_db.saveNetizen(nickName);
    return true;
}

bool Server::logNetizen(std::string nickName, int clientSocket, int clientPort)
{
    for (auto& it : m_netizens) {
        if (it.getName() == nickName) {
            it.updateInfo(clientSocket, this);
            m_clients[clientPort] = nickName;
            m_sockets[clientPort] = clientSocket;
            return true;
        }
    }
    return false;
}

void Server::delNetizen(std::string nickName)
{
    m_db.delNetizen(nickName);
    for(auto& it : m_netizens){
        it.delFriend(nickName);     //使所有用户删除该用户好友
    }

    for(auto it = m_netizens.begin();it != m_netizens.end();it++){
        if(it->getName() == nickName){
            m_netizens.erase(it);
            int netizenPort;
            for(auto& it : m_clients){
                if(it.second == nickName){
                    netizenPort = it.first;
                    break;
                }
            }
            m_clients.erase(netizenPort);
            m_sockets.erase(netizenPort);
            break;
        }
    }
}

void Server::clientProcess(std::string& msg,int clientPort)   //初步处理接收到的客户端信息
{
    int clientSocket{m_sockets[clientPort]};
    std::istringstream ss{msg};
    std::string command;
    std::string arguments;
    ss >> command;
    if(command == "/signUp"){   //不存在用户
        ss >> arguments;
        if(!regNetizen(arguments,clientSocket,clientPort)){
            arguments = "failed";
        }
        send(clientSocket,arguments.c_str(),arguments.size(),0);
    }else{                      //委托用户发送对应信息存在用户
        if (command == "/logIn") {
            ss >> arguments;
            if (!logNetizen(arguments, clientSocket, clientPort)) {
                arguments = "failed";
            }
            send(clientSocket, arguments.c_str(), arguments.size(), 0);
        } else {
            for (auto& it : m_netizens) {
                if (it.getName() == m_clients[clientPort]) {
                    it.sendMessage(msg);
                    break; //找到后跳出避免多余性能消耗
                }
            }
        }
    }
}

void Server::msgProcess(Message& msg)   //处理信息
{
    if (msg.m_type == "normal") {
        std::string reply{msg._sender->getName() + ": " + msg.m_context};
        for(auto& it : m_clients){
            if(it.second != msg._sender->getName()){
                int clientPort{it.first};
                send(m_sockets[clientPort],reply.c_str(),reply.size(),0);
            }
        }
    } else if (msg.m_type == "command") {
        std::istringstream ss{msg.m_context};
        std::string command;
        std::string arguments;
        ss >> command;

        if(command == "/list"){ //委托Neitzen类处理列出所有朋友
            msg._sender->listFriends();
        }else if(command == "/help"){
            for(auto& it : m_clients){
                if(it.second == msg._sender->getName()){
                    int clientPort{it.first};
                    send(m_sockets[clientPort],"/friend <name>       Add friend.\n/del <name>          Delete friend.\n/del <name>          Delete friend.\n/list                List friends.",1024,0);
                }
            }
        }else if(command == "/friend"){ //委托Netizen类处理添加好友事件
            ss >> arguments;

            if(arguments.empty()){  //未指定用户名
                for(auto& it : m_clients){
                    if(it.second == msg._sender->getName()){
                        int clientPort{it.first};
                        std::string reply{"name is empty."};
                        send(m_sockets[clientPort],reply.c_str(),reply.size(),0);
                    }
                }
            }else{
                for(auto& it: m_netizens){
                    if(it.getName() == arguments){
                        msg._sender->sendFriendRequest(&it);
                        break; //找到后跳出避免多余性能消耗
                    }
                }
            }
        } else if (command == "/m") { //私聊
            ss >> arguments;
            std::string context;
            ss >> context;

            if (arguments.empty()) { //未指定用户名
                for (auto& it : m_clients) {
                    if (it.second == msg._sender->getName()) {
                        int clientPort{it.first};
                        std::string reply{"name is empty."};
                        send(m_sockets[clientPort], reply.c_str(), reply.size(), 0);
                    }
                }
            } else {
                for (auto& it : m_clients) {
                    if (it.second == arguments) {
                        int clientPort{it.first};
                        std::string reply{msg._sender->getName() + " 私聊: " + context};
                        send(m_sockets[clientPort], reply.c_str(), reply.size(), 0);
                        break; //找到后跳出避免多余性能消耗
                    }
                }
            }
        } else if (command == "/del") {
            ss >> arguments;

            if (arguments.empty()) { //未指定用户名
                for (auto& it : m_clients) {
                    if (it.second == msg._sender->getName()) {
                        int clientPort{it.first};
                        std::string reply{"name is empty."};
                        send(m_sockets[clientPort], reply.c_str(), reply.size(), 0);
                    }
                }
            } else {
                msg._sender->delFriend(arguments);
            }
        } else { //未知命令处理

            for (auto& it : m_clients) {
                if (it.second == msg._sender->getName()) {
                    int clientPort{it.first};
                    std::string reply{"Unkown command."};
                    send(m_sockets[clientPort], reply.c_str(), reply.size(), 0);
                }
            }
        }
    }
}
