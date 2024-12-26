// 2023051604044 万睿
// 2024-12-25
// 客户端交互相关

#ifndef CLIENT_H
#define CLIENT_H

extern void startUp();
extern bool signUp(int& clientSocket);
extern int connect2Server();
extern void sendMsg2Server(int& clientSocket);
extern void receiveFromServer(int clientSocket);

#endif // CLIENT_H
