#ifndef NOTICEENTITY_H
#define NOTICEENTITY_H
#include <QSqlRecord>
#include "src/common/erpsqltablemodel.h"
#include "src/common/helptool.h"
#include "src/entity/entity.h"

class NoticeEntity : public Entity
{
public:
    NoticeEntity();

    ErpSqlTableModel* getPage(int page, int pageSize = 20);
    ErpSqlTableModel* getPage(QString condition, int page, int pageSize = 20);
    QMap<QString, QVariant> getOne(int id);
    bool insert(QMap<QString, QVariant>& data);
    bool update(QMap<QString, QVariant>& data, int id);
    bool updateStatus(int id);

    QString mtable;

private:
    //QSqlQueryModel *allList;
    ErpSqlTableModel *pageList;
    QMap<QString, QVariant> currentData;
};

#endif // NOTICEENTITY_H
