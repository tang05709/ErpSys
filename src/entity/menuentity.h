#ifndef MENUENTITY_H
#define MENUENTITY_H
#include <QSqlQueryModel>
#include <QSqlRecord>
#include "src/entity/entity.h"

class MenuEntity : public Entity
{
public:
    MenuEntity();

    QSqlQueryModel* getAll();
    bool insert(QMap<QString, QVariant>& data);
    QString mtable;

private:
    QSqlQueryModel *allList;
};

#endif // MENUENTITY_H
