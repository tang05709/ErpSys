#ifndef MENULIST_H
#define MENULIST_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include "src/entity/menuentity.h"

namespace Ui {
class MenuList;
}

class MenuList : public QWidget
{
    Q_OBJECT

public:
    explicit MenuList(QWidget *parent = nullptr);
    ~MenuList();

     void initTable();

private:
    Ui::MenuList *ui;

    QStringList titles;
    MenuEntity *entity;
    QStandardItemModel treeModel;
    QSqlQueryModel *list;
};

#endif // MENULIST_H
