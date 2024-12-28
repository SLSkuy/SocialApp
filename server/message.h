// 2023051604044 万睿
// 2024-12-23
// Message类接口

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>

#include "netizen.h"

// class Message
// {
// public:
//     Message(Netizen* sender,std::string context,std::string type) : _sender(sender),m_context(context),m_type(type) {}
//     std::string getContext() {return m_context;}
//     std::string getType() {return m_type;}
//     Netizen* getSender() {return _sender;}
//     Netizen* getReceiver() {return _receiver;}
// private:
//     std::string m_context;
//     std::string m_type;
//     Netizen* _sender;
//     Netizen* _receiver;
// };

struct Message
{
    Message(Netizen* sender,std::string context,std::string type) : _sender(sender),m_context(context),m_type(type) {}
    std::string m_context;
    std::string m_type;
    Netizen* _sender;
    Netizen* _receiver;
};

#endif // MESSAGE_H
