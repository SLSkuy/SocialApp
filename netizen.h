// 2023051604044 万睿
// 2024-12-23
// Netizen类接口

#ifndef NETIZEN_H
#define NETIZEN_H

#include <string>
#include <vector>

class Netizen
{
public:
    Netizen(std::string name) : m_nickName(name){ logIn();}    //登陆账号
    void logIn();
    void sendFriendRequest(std::string name);
    bool acceptFriendRequest(std::string name);
    void delFriend(std::string name);
    void sendMessage(std::string context);
    void listFriends();
    bool hasId(std::string name);
private:
    std::string m_account;
    std::string m_nickName;
    int m_clientSocket;
    std::vector<Netizen*> _friends;
};

#endif // NETIZEN_H
