#ifndef DEPARTMENTLIST_H
#define DEPARTMENTLIST_H

#include <QWidget>
#include "src/common/erpsqltablemodel.h"
#include "src/entity/departmententity.h"
#include "src/employeemanager/departmentadd.h"
#include "src/erpdelegate/tableeditanddeletedelegate.h"

namespace Ui {
class DepartmentList;
}

class DepartmentList : public QWidget
{
    Q_OBJECT

public:
    explicit DepartmentList(QWidget *parent = nullptr);
    ~DepartmentList();
    void initTable();

private slots:
    void editData(const QModelIndex& index);
    void deleteData(const QModelIndex& index);
    void on_btnAdd_clicked();

private:
    Ui::DepartmentList *ui;

    DepartmentEntity *entity;
    ErpSqlTableModel *all;
    TableEditAndDeleteDelegate *tableEditAndDeleteDelegate;
};

#endif // DEPARTMENTLIST_H
