#ifndef EMPLOYEEENTITY_H
#define EMPLOYEEENTITY_H
#include <QSqlRecord>
#include "src/common/erpsqltablemodel.h"
#include "src/common/helptool.h"
#include "src/entity/entity.h"

class EmployeeEntity : public Entity
{
public:
    EmployeeEntity();

    ErpSqlTableModel* getPage(int page, int pageSize = 20);
    QMap<QString, QVariant> getOne(int id);
    bool insert(QMap<QString, QVariant>& data);
    bool update(QMap<QString, QVariant>& data, int id);
    QString mtable;

private:
    ErpSqlTableModel *pageList;
    QMap<QString, QVariant> currentData;
};

#endif // EMPLOYEEENTITY_H
