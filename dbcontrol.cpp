//2023051604032 王新凯 2024/12/25
//DBControl类实现
//数据库的连接以及数据的读取

#include "dbcontrol.h"

#include <mysql++/mysql++.h>
#include <iostream>
using std::cerr;
using std::endl;
#include <string>

bool DBControl::initDB() //连接数据库
{
    mysqlpp::Query query = m_connection.query();
    query.reset();
    if (m_connection.connect("socialapp", nullptr, "root", "root")) {
        cerr << "连接数据库成功，找到socialapp数据库" << endl;
    } else {
        if (m_connection.connect(nullptr, nullptr, "root", "root")) {
            cerr << "连接数据库成功,未找到socialapp数据库，创建socialapp数据库" << endl;
            query.reset();
            query << "Create database socialapp;";
            if (query.exec()) {
                cerr << "创建socialapp数据库成功" << endl;
                query.reset();
                query << "use socailapp;";
                if (query.exec())
                    cerr << "成功切换到socialapp数据库" << endl;
                else {
                    cerr << "切换到socialapp数据库失败" << endl;
                    return false;
                }
            } else {
                cerr << "创建socialapp数据库失败\n";
                return false;
            }
        } else {
            cerr << "连接数据库失败\n";
            return false;
        }
    }
    return true;
}

bool DBControl::loadNetizens(std::vector<Netizen> &netizens)
{
    mysqlpp::Query query = m_connection.query();
    query.reset();
    query << "Select * From netizens; ";
    if (mysqlpp::StoreQueryResult result = query.store()) {
        for (int i{0}; i != result.num_rows(); i++) {
            netizens.emplace_back(
                (std::string) result[i][0],
                (std::string) result[i][1]); //ToDo:netizen缺少nickname//////////////////////////
        } /*
        for (auto &netizen : netizens) {
            query.reset();
            query << "Select friend From" + netizen.getAccount() + ";";
            if (mysqlpp::StoreQueryResult result = query.store()) {
                for (int i{0}; i != result.num_rows(); i++) {
                    netizen.addFriend(result[i][0]);
                }
            }
            cerr << "导入成功" << endl;
        }*/
    } else {
        cerr << "未找到账户信息" << endl;
        query.reset();
        query << "Create Table netizens (account char(32) Primary Key, nickname char(32) );";
        if (query.execute()) {
            cerr << "创建netizens表成功:" << query.error() << endl;
        } else {
            cerr << "创建netizens表失败:" << query.error() << endl;
            return false;
        }
    }
    return true;
}

bool DBControl::saveNetizen(Netizen &netizen)
{
    mysqlpp::Query query = m_connection.query();
    query.reset();
    if (netizen.getAccount() == "netizens") {
        cerr << "不准账户名为\"netizens\"";
        return false;
    }
    //ToDo好友保存待实现///////////////////////////////////////////////////////////
    query << "Insert Into netizens Value ('" + netizen.getAccount() + "','" + netizen.getNickname()
                 + "');";
    if (query.exec())
        cerr << "保存成功" + netizen.getNickname() << endl;
    else
        cerr << "保存失败:" + netizen.getNickname() << endl;
    return true;
}
/*
void DBControl::loadMessages(std::vector<Message> &messages, std::vector<Netizen> &netizens)
{
    mysqlpp::Query query = m_connection.query();
    query << "Select * From messages; ";
    if (mysqlpp::StoreQueryResult result = query.store()) {
        for (int i{0}; i != result.num_rows(); i++) {
            messages.emplace_back((std::string) result[i][0], (std::string) result[i][1]);
        }
        cerr << "导入成功" << endl;
    } else {
        cerr << "未找到消息信息" << endl;
        query.reset();
        query << "Create Table messages ( time char(32), content text, sender char(32), receiver "
                 "char(32), Primary Key(time,sender,receiver) "
                 "char(32));";
        if (query.execute()) {
            cerr << "创建messages表成功:" << query.error() << endl;
        } else
            cerr << "创建messages表失败:" << query.error() << endl;
    }
}*/
