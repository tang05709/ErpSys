#ifndef DEPARTMENTADD_H
#define DEPARTMENTADD_H

#include <QDialog>
#include "src/entity/departmententity.h"

namespace Ui {
class DepartmentAdd;
}

class DepartmentAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DepartmentAdd(QWidget *parent = nullptr, int id = 0);
    ~DepartmentAdd();
    void initForm();

private slots:
    void on_btnFormSubmit_clicked();

    void on_btnFormClose_clicked();

private:
    Ui::DepartmentAdd *ui;

    DepartmentEntity *entity;
    int mid = 0;
};

#endif // DEPARTMENTADD_H
