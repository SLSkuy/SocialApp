// 2023051604044 万睿
// 2024-12-23
// Netizen类实现

#include "netizen.h"

#include <string>
#include <iostream>
using std::cin;     using std::cout;    using std::endl;    using std::cerr;
#include <sys/socket.h>
#include <arpa/inet.h>
#include <limits>

//TODO:测试函数
extern std::vector<Netizen> netizens;

void Netizen::addFriend(std::string friendAccount)
{
    for (auto &i : netizens) {
        if (i.getAccount() == friendAccount)
            _friends.push_back(&i); //TODO:未使用hasId///////////////////////////////////////////////
    }
}
//测试

void Netizen::signUp()
{
    m_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_clientSocket <= 0) {
        cerr << "Socket creation failed!" << endl;
        return;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(8080);

    if (connect(m_clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        cout << "connect failed" << endl;
        return;
    }

    sendMessage();
}

void Netizen::sendMessage()
{
    std::string buf;
    while (true) {
        buf.clear();

        cout << "Enter message: ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(),
                   '\n'); //刷新输入留缓冲区防止多余信息写入缓冲区
        cin >> buf;

        // 发送消息到服务器
        send(m_clientSocket, buf.c_str(), sizeof(buf.c_str()), 0);
    }
}
