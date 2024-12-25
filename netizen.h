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
    Netizen(std::string account) : m_account(account){ logIn();}    //登陆账号
    void logIn();
    void sendFriendRequest(std::string);
    bool acceptFriendReques(std::string);
    void delFriend(std::string);
    void sendMessage();
    void listFriends();
    bool hasId(std::string);
private:
    std::string m_account;
    std::string m_nickName;
    int m_clientSocket;
    int m_port;
    std::vector<Netizen*> _friends;
};

#endif // NETIZEN_H
