#ifndef ENTITY_H
#define ENTITY_H
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include "src/common/readini.h"

class Entity
{
public:
    Entity(QString tName);
    virtual~Entity();
    void dbConn(); // 建立连接
    bool sqlExec(QString sql);  // 执行sql语句
    void where(QString cond); // where条件， 传递字符串，类似" name =  and password = "
    void orderBy(QString orders); // order排序 传递字符串，类似" id desc, age desc "
    void fields(QString field); // 要查询的字段, 类似 "name, password"
    void limit(int page, int pageSize = 20); // 分页
    void leftJoin(QString table, QString primaryKey, QString foreignKey); // 关联， table表名，primaryKey主键，foreignKey 外键
    int getCount(); // 返回总数量
    QString joinSqlStrForQueryModel(); // 拼接sql

private:
    ReadIni *readIni;
    QSqlDatabase DB; //数据库连接

    QString tableName; // 数据库名称
    QString leftJoinStr; // join字符串
    QString whereStr; // where字符串
    QString orderStr; // order字符串
    QString fieldStr; // field字符串
    QString limitStr; // limit字符串
};

#endif // ENTITY_H
