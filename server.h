// 2023051604044 万睿
// 2024-12-23
// 网络聊天声明

#ifndef SERVER_H
#define SERVER_H

#include "netizen.h"

#include <unordered_map>
#include <vector>
#include <string>

class Server
{
public:
    Server(std::string ip,std::string port) : m_IP(ip),m_Port(port) {initServer();}
    void regNetizen();
    void delNetizen();
    void initServer();
    void handleClientSocket(int serverFd);
    void handleClientMessage(int socketFd,int port);
    int m_serverSocket;
private:
    std::string m_IP;
    std::string m_Port;
    std::unordered_map<std::string,int> _clientFds; //(account,password)
    std::vector<Netizen*> _netizens;
};

extern void startServer();


#endif // SERVER_H
