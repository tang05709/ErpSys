#include "entity.h"
#include <QMessageBox>

Entity::Entity(QString tName) : tableName(tName)
{
    dbConn();
}

Entity::~Entity()
{
    if (DB.open()) {
        DB.close();
    }
}

void Entity::dbConn()
{
    readIni = new ReadIni();
    QMap<QString, QString> config = readIni->getMySqlIni();
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        DB = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        DB = QSqlDatabase::addDatabase("QMYSQL");
        DB.setHostName(config["host"]);
        DB.setDatabaseName(config["dbname"]);
        DB.setUserName(config["dbuser"]);
        DB.setPassword(config["dbpassword"]);
        DB.setPort(config["dbport"].toInt());
        if (!DB.open()) {
            QMessageBox::information(0, "提示", "数据库连接失败");
        }
    }

}


bool Entity::sqlExec(QString sql)
{
    QSqlQuery query;
    if (query.exec(sql)) {
        return true;
    }
    return false;
}

void Entity::where(QString cond)
{
    if (!cond.isEmpty()) {
        whereStr = " WHERE " + cond;
    }
}


void Entity::orderBy(QString orders)
{
    if (!orders.isEmpty()) {
        orderStr = " ORDER BY " + orders;
    }
}

void Entity::fields(QString field)
{
    if (!field.isEmpty()) {
        fieldStr = field;
    }
}

void Entity::limit(int page, int pageSize)
{
    if (page >= 0) {
        //" limit 5, 20";
        int opage = (page-1) * pageSize;
        limitStr = QString(" LIMIT %1, %2 ").arg(opage).arg(pageSize);
    }
}

// 多个join使用多个leftJoin
void Entity::leftJoin(QString table, QString primaryKey, QString foreignKey)
{
    // from erp_employees as
    // left join erp_duties on erp_employees.duty_id = erp_duties.id
    leftJoinStr += QString(" LEFT JOIN %1 ON %2 = %3").arg(table).arg(primaryKey).arg(foreignKey);
}

int Entity::getCount()
{
    int count = 0;
    QString sqlStr = "";
    // join
    if (!leftJoinStr.isEmpty()) {
        sqlStr += leftJoinStr;
    }
    // where
    if (!whereStr.isEmpty()) {
        sqlStr += whereStr;
    }
    QString lastSql = QString("SELECT COUNT(*) FROM %1 %2").arg(tableName).arg(sqlStr);

    QSqlQuery query;
    query.exec(lastSql);
    if (query.next()) {
         count = query.value(0).toInt();
    }

    return count;
}

QString Entity::joinSqlStrForQueryModel()
{
    // field
    if (fieldStr.isEmpty()) {
        fieldStr = " * ";
    }

    QString sqlStr = "";
    // join
    if (!leftJoinStr.isEmpty()) {
        sqlStr += leftJoinStr;
    }
    // where
    if (!whereStr.isEmpty()) {
        sqlStr += whereStr;
    }
    // order by
    if (!orderStr.isEmpty()) {
        sqlStr += orderStr;
    }
    // limit
    if (!limitStr.isEmpty()) {
        sqlStr += limitStr;
    }


    QString lastSql  = QString("SELECT %1 FROM %2 %3").arg(fieldStr).arg(tableName).arg(sqlStr);

    return lastSql;
}
