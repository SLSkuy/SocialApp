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
    Netizen(std::string name, int clientSocket, Server* server)
        : m_nickName(name)
        , m_clientSocket(clientSocket)
        , _server(server)
        , m_onLine{true}
    {}
    Netizen(std::string name) : m_nickName(name), m_onLine{false}
    {}
    void sendFriendRequest(Netizen* target);
    bool acceptFriendRequest(Netizen* target);
    void delFriend(std::string name);
    void sendMessage(std::string context);
    void listFriends();
    bool hasId(std::string name);
    void addFriend(Netizen* target);
    std::string getName() {return m_nickName;} //Server处理找到指定Netizen对象
    void updateInfo(int clientSocket, Server* server); //登录时更新与服务器相关信息
    bool status()
    {
        return m_onLine;
    }

private:
    std::string m_nickName;
    int m_clientSocket;
    std::vector<Netizen*> _friends;
    Server* _server;
    bool m_onLine;
};

#endif // NETIZEN_H
