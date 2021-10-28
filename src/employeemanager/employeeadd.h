#ifndef EMPLOYEEADD_H
#define EMPLOYEEADD_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QButtonGroup>
#include "src/entity/departmententity.h"
#include "src/entity/dutyentity.h"
#include "src/entity/employeeentity.h"

namespace Ui {
class EmployeeAdd;
}

class EmployeeAdd : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeAdd(QWidget *parent = nullptr, int id = 0);
    ~EmployeeAdd();

    void initForm();

private slots:
    void on_btnFormClose_clicked();

    void on_btnFormSubmit_clicked();

private:
    Ui::EmployeeAdd *ui;

    QButtonGroup *sexGroup;
    EmployeeEntity *entity;
    int mid = 0;
};

#endif // EMPLOYEEADD_H
