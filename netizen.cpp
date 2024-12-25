// 2023051604044 万睿
// 2024-12-23
// Netizen类实现

#include "netizen.h"
#include "message.h"

#include <iostream>
#include <vector>

extern std::vector<Netizen> netizens;

void Netizen::logIn()
{

}

void Netizen::sendFriendRequest(std::string name)
{
    if(hasId(name)){
        std::cout << name << "is already your friend" << std::endl;
        return;
    }else{
        for(auto& it : netizens){
            if(it.m_nickName == name){
                if(it.acceptFriendRequest(m_nickName)){
                    std::cout << name << " agrees to become your friend." << std::endl;
                    _friends.emplace_back(&it);
                    it._friends.emplace_back(this);
                }else{
                    std::cout << name << " reject to be your friend." << std::endl;
                }
            }
        }
    }
}

bool Netizen::acceptFriendRequest(std::string name)
{
    std::cout << name << " want to be your friend.\n"
                << "Do you agree?(Y/N): ";
    std::string input;
    while(std::cin >> input){
        if(input == "Y" || input == "y")
        {
            return true;
        }else if(input == "N" || input == "n"){
            return false;
        }else{
            std::cout << "Please input Y or N: ";
        }
    }
    return false;
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
            std::cout << "you don't have a friend named: " << name << std::endl;
        }
    }
}

void Netizen::sendMessage(std::string context)
{

}   

void Netizen::listFriends()
{
    if(_friends.size() == 0)
    {
        std::cout << "you haven't made any friends yet." << std::endl;
        return;
    }

    std::cout << m_nickName << "'s friends are listed below:\n";
    for(auto& it : _friends){
        std::cout << it->m_nickName << ' ';
    }
    std::cout << std::endl;
}

bool Netizen::hasId(std::string name)
{
    for(auto& it : _friends){
        if(it->m_nickName == name)return true;
    }
    return false;
}