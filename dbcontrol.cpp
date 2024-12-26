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

    query << "Show Tables Like 'netizens';";
    if (query.store().num_rows()) {
        cerr << "找到账户信息" << endl;
    } else {
        cerr << "未找到账户信息" << endl;
        query << "Create Table netizens (account char(32) Primary Key, nickname char(32) );";
        if (query.exec()) {
            cerr << "创建netizens表成功:" << query.error() << endl;
        } else {
            cerr << "创建netizens表失败:" << query.error() << endl;
            return false;
        }
    }

    query << "Show Tables Like 'friends';";
    if (query.store().num_rows()) {
        cerr << "找到好友信息" << endl;
    } else {
        cerr << "未找到好友信息" << endl;
        query << "Create Table friends (account char(32), friend char(32),Primary "
                 "Key(account,friend));";
        if (query.exec()) {
            cerr << "创建friends表成功:" << query.error() << endl;
        } else {
            cerr << "创建friends表失败:" << query.error() << endl;
            return false;
        }
    }
    return true;
}

bool DBControl::loadNetizens(std::vector<Netizen> &netizens) //从数据库导入
{
    mysqlpp::Query query = m_connection.query();
    query << "Select * From netizens; ";
    if (mysqlpp::StoreQueryResult result = query.store()) {
        for (int i{0}; i != result.num_rows(); i++) {
            netizens.emplace_back((std::string) result[i][0], (std::string) result[i][1]);
        }
        for (auto &netizen : netizens) {
            query.reset();
            query << "Select friend From friends Where account=" + netizen.getAccount() + ";";
            if (mysqlpp::StoreQueryResult result = query.store()) {
                for (int i{0}; i != result.num_rows(); i++) {
                    netizen.addFriend((std::string) result[i][0]);
                }
            }
        }
    } else {
        {
            cerr << "loadNetizens未找到账户信息" << endl;
            return false;
        }
    }
    cerr << "导入成功" << endl;
    return true;
}

bool DBControl::saveNetizen(std::string account, std::string nickname) //保存账户
{
    mysqlpp::Query query = m_connection.query();

    query << "Insert Into netizens Value ('" + account + "','" + nickname + "');";
    if (!query.exec()) {
        cerr << "保存失败:" + account << endl;
        return false;
    }
    return true;
}

bool DBControl::delNetizen(std::string account) //删除账户
{
    mysqlpp::Query query = m_connection.query();
    query << "Delete From netizens Where account = '" + account
                 + "';Delete From friends Where account = '" + account
                 + "';Delete From friends Where friend = '" + account + "';";
    if (!query.exec()) {
        cerr << "删除失败:" + account << endl;
        return false;
    }
    return true;
}

bool DBControl::updateNickname(std::string account, std::string nickname) //更新昵称
{
    mysqlpp::Query query = m_connection.query();
    query << "Update netizens Set nickname='" + nickname + "' Where account='" + account + "';";
    if (!query.exec()) {
        cerr << "更新错误:" + account + "!";
        return false;
    }

    return true;
}

bool DBControl::saveFriend(std::string netizen1, std::string netizen2) //保存指定好友
{
    mysqlpp::Query query = m_connection.query();

    query << "Insert Into friends Value ('" + netizen1 + "','" + netizen2 + "'),('" + netizen2
                 + "','" + netizen1 + "');";
    if (!query.execute()) {
        cerr << "保存好友失败:" + netizen1 + " " + netizen2 << endl;
        return false;
    }

    return true;
}

bool DBControl::delFriend(std::string netizen1, std::string netizen2) //删除指定好友
{
    mysqlpp::Query query = m_connection.query();
    query << "Delete From friends Where account = '" + netizen1 + "' AND friend = '" + netizen2
                 + "';";
    if (!query.exec()) {
        cerr << "删除失败:" + netizen1 + "  " + netizen2 << query.error() << endl;
        return false;
    }
    query << "Delete From friends Where friend = '" + netizen1 + "' AND account = '" + netizen2
                 + "';";
    if (!query.exec()) {
        cerr << "删除失败:" + netizen1 + "  " + netizen2 << query.error() << endl;
        return false;
    }
    return true;
}

/*//TODO:信息处理是否保留
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
