// 2023051604044 万睿
// 2024-12-23
// Netizen类接口

#ifndef NETIZEN_H
#define NETIZEN_H

#include <string>
#include <vector>

class Server;

class Netizen
{
public:
    Netizen(std::string name,int clientSocket,Server* server)
        : m_nickName(name),m_clientSocket(clientSocket),_server(server) {}
    void sendFriendRequest(Netizen* target);
    bool acceptFriendRequest(Netizen* target);
    void delFriend(std::string name);
    void sendMessage(std::string context);
    void listFriends();
    bool hasId(std::string name);
    std::string getName(){return m_nickName;}
private:
    std::string m_nickName;
    int m_clientSocket;
    std::vector<Netizen*> _friends;
    Server* _server;
};

#endif // NETIZEN_H
