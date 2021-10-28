#ifndef DUTYENTITY_H
#define DUTYENTITY_H
#include <QSqlRecord>
#include "src/common/erpsqltablemodel.h"
#include "src/common/helptool.h"
#include "src/entity/entity.h"

class DutyEntity : public Entity
{
public:
    DutyEntity();
    ErpSqlTableModel* getAll();
    QMap<QString, QVariant> getOne(int id);
    bool insert(QMap<QString, QVariant>& data);
    bool update(QMap<QString, QVariant>& data, int id);
    QString mtable;

private:
    ErpSqlTableModel *all;
    QMap<QString, QVariant> currentData;
};

#endif // DUTYENTITY_H
