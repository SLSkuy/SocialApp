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
    Netizen(std::string account,std::string name) : m_account(account),m_nickName(name){}
    void sendFriendRequest(std::string);
    bool acceptFriendReques(std::string);
    void sendMessage();
    void checkHistory();
    void listFriends();
    bool hasId(std::string);
private:
    std::string m_account;
    std::string m_nickName;
    std::vector<Netizen*> _friends;
};

#endif // NETIZEN_H
