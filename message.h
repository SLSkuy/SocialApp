// 2023051604044 万睿
// 2024-12-23
// Message类接口

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>

#include "netizen.h"

class Message
{
public:
    Message();
private:
    std::string m_time;
    std::string m_context;
    Netizen* _sender;
    std::vector<Netizen*> _receiver;
};

#endif // MESSAGE_H
