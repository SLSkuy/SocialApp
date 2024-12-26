// 2023051604044 万睿
// 2024-12-23
// Netizen类实现

#include "netizen.h"
#include "message.h"
#include "server.h"

#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <vector>
#include <string>

void Netizen::sendFriendRequest(Netizen* target)
{
    if(hasId(target->m_nickName)){
        //std::cout << target->m_nickName << "is already your friend" << std::endl;
        std::string reply{target->m_nickName + "is already your friend."};
        send(m_clientSocket,reply.c_str(),reply.size(),0);
        return;
    }else{
        if(target->acceptFriendRequest(this)){
            target->_friends.emplace_back(this);
            this->_friends.emplace_back(target);
            std::string reply{target->m_nickName + " agree to be your friend."};
            send(m_clientSocket,reply.c_str(),reply.size(),0);
        }else{
            std::string reply{target->m_nickName + " disagree to be your friend."};
            send(m_clientSocket,reply.c_str(),reply.size(),0);
        }
    }
}

bool Netizen::acceptFriendRequest(Netizen* target)
{
    //std::cout << target->m_nickName << " want to be your friend.\n" << "Do you agree?(Y/N): ";
    std::string reply{target->m_nickName + " want to be your friend.\nDo you agree?(Y/N): "};
    send(m_clientSocket,reply.c_str(),reply.size(),0);

    return true;
}

void Netizen::delFriend(std::string name)
{
    for(auto it = _friends.begin();it != _friends.end();it++){
        if((*it)->m_nickName == name){  //查找是否存在对应名称的好友
            for(auto buf = (*it)->_friends.begin();it != (*it)->_friends.end();it++)    //若存在双向删除好友
            {
                if((*buf)->m_nickName == this->m_nickName){
                    (*it)->_friends.erase(buf);
                    break;
                }
            }
            _friends.erase(it);
            break;
        }else{
            //std::cout << "you don't have a friend named: " << name << std::endl;
        }
    }
}

void Netizen::sendMessage(std::string context)
{
    std::string type{"normal"};
    if(context[0] == '/'){
        type = "command";
    }
    Message msg(this,context,type);
    _server->msgProcess(msg);   //委托服务端处理信息
}   

void Netizen::listFriends()
{
    if(_friends.size() == 0)
    {
        //std::cout << "you haven't made any friends yet." << std::endl;
        std::string reply{"you haven't made any friends yet."};
        send(m_clientSocket,reply.c_str(),reply.size(),0);
        return;
    }

    //std::cout << m_nickName << "'s friends are listed below:\n";
    std::string reply{"your friends are listed below:\n"};
    for(auto& it : _friends){
        reply += it->m_nickName;
        //std::cout << it->m_nickName << ' ';
    }
    send(m_clientSocket,reply.c_str(),reply.size(),0);
    //std::cout << std::endl;
}

bool Netizen::hasId(std::string name)
{
    for(auto& it : _friends){
        if(it->m_nickName == name)return true;
    }
    return false;
}
