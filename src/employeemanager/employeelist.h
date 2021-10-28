#ifndef EMPLOYEELIST_H
#define EMPLOYEELIST_H

#include <QWidget>
#include "src/common/erpsqltablemodel.h"
#include "src/entity/employeeentity.h"
#include "src/employeemanager/employeeadd.h"
#include "src/erpdelegate/tableeditanddeletedelegate.h"
#include "src/erpdelegate/departmentdelegate.h"

namespace Ui {
class EmployeeList;
}

class EmployeeList : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeList(QWidget *parent = nullptr);
    ~EmployeeList();

     void initTable();

private slots:
     void editData(const QModelIndex& index);
     void deleteData(const QModelIndex& index);
     void on_btnAdd_clicked();

     void on_btnPageFirst_clicked();

     void on_btnPagePrev_clicked();

     void on_btnPageNext_clicked();

     void on_btnPageLast_clicked();

private:
    Ui::EmployeeList *ui;

    EmployeeEntity *entity;
    ErpSqlTableModel *pageList;
    TableEditAndDeleteDelegate *tableEditAndDeleteDelegate;
    DepartmentDelegate *departmentDelegate;

    int page = 1;
    int pageSize = 20;
    int count = 0;
    int pageCount = 0;
};

#endif // EMPLOYEELIST_H
