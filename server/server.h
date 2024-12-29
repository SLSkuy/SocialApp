// 2023051604044 万睿
// 2024-12-23
// 服务端声明

#ifndef SERVER_H
#define SERVER_H

#include "netizen.h"
#include "message.h"
#include "dbcontrol.h"

#include <unordered_map>
#include <vector>
#include <string>

class Server
{
public:
    Server(std::string ip,std::string port) : m_IP(ip),m_Port(port) {}
    bool logNetizen(std::string nickName, int clientSocket, int clientPort);
    bool regNetizen(std::string nickName,int clientSocket,int clientPort);
    void delNetizen(std::string nickName);
    void initServer();
    void handleClientSocket();
    void handleClientMessage(int clinetSocket,int clientPort);
    void clientProcess(std::string& msg,int clientPort);
    void msgProcess(Message& msg);
private:
    int m_serverSocket;
    std::string m_IP;
    std::string m_Port;
    std::unordered_map<int,std::string> m_clients; //(port,name)
    std::unordered_map<int,int> m_sockets; //(port,socket)
    std::vector<Netizen> m_netizens;
    DBControl m_db;
};

#endif // SERVER_H
