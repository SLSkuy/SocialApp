//2023051604032 王新凯 2024/12/25
//DBControl类
//数据库的连接以及数据的读取

#pragma once

#include <mysql++/mysql++.h>
#include <vector>
#include "netizen.h"
#include "message.h"

class DBControl
{
    public:
    bool initDB(); //连接数据库
    bool loadNetizens(std::vector<Netizen> &netizens); //从数据库导入
    bool saveNetizen(std::string account); //保存账户(不保存好友!)
    bool delNetizen(std::string account); //删除账户（顺带删除好友!）
    bool saveFriend(std::string netizenAccount, std::string friendAccount); //保存指定好友
    bool delFriend(std::string netizenAccount, std::string friendAccount); //删除指定好友

private:
    mysqlpp::Connection m_connection{false};
};
