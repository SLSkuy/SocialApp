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
    bool loadNetizens(std::vector<Netizen> &netizens);
    bool saveNetizen(Netizen &netizen);
    //void loadMessages(std::vector<Message> &messages);

    private:
    mysqlpp::Connection m_connection{false};
};
