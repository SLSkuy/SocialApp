// 2023051604044 万睿
// 2024-12-25
// 客户端交互相关

#ifndef CLIENT_H
#define CLIENT_H

#include <string>

extern std::string getIP();
extern bool signUp(int& clientSocket);
extern int connect2Server(std::string IP);
extern void sendMsg2Server(int& clientSocket);
extern void receiveFromServer(int clientSocket);
extern bool logIn(int& clientSocket);

#endif // CLIENT_H
