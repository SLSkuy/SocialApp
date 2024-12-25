// 2023051604044 万睿
// 2024-12-23
// 服务端声明

#ifndef SERVER_H
#define SERVER_H

#include "netizen.h"

#include <unordered_map>
#include <vector>
#include <string>

class Server
{
public:
    Server(std::string ip,std::string port) : m_IP(ip),m_Port(port) {}
    void regNetizen();
    void delNetizen();
    void initServer();
    void handleClientSocket();
    void handleClientMessage(int socketFd,int port);
    void msgProcess(std::string& msg);
private:
    int m_serverSocket;
    std::string m_IP;
    std::string m_Port;
    std::unordered_map<std::string,int> _clientSockets; //(name,socket)
    std::unordered_map<int,int> _ports; //(port,socket)
    std::vector<Netizen> _netizens;
};

void startServer(); //启动服务器 后续客户服务端分离后可写入服务端主函数

#endif // SERVER_H
