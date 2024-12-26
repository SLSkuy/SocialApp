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
Netizen(std::string account, std::string nickname) : m_account(account), m_nickName{nickname}
{
    //logIn();
} //登陆账号
Netizen()
{
    signUp();
} //注册账号
    void signUp();
    void logIn();
    void sendFriendRequest(std::string);
    bool acceptFriendReques(std::string);
    void delFriend(std::string);
    void sendMessage();
    void listFriends();
    bool hasId(std::string);
    //临时
    void addFriend(std::string friendAccount); //强行加好友单向

    std::string getAccount()
    {
        return m_account;
    }
    std::string getNickname()
    {
        return m_nickName;
    }
    //
    private:
    std::string m_account;
    std::string m_nickName;
    int m_clientSocket;
    std::vector<Netizen*> _friends;
};

#endif // NETIZEN_H
