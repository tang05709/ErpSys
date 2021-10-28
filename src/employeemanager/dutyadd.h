#ifndef DUTYADD_H
#define DUTYADD_H

#include <QDialog>
#include "src/entity/dutyentity.h"

namespace Ui {
class DutyAdd;
}

class DutyAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DutyAdd(QWidget *parent = nullptr, int id = 0);
    ~DutyAdd();

    void initForm();

private slots:
    void on_btnFormSubmit_clicked();

    void on_btnFormClose_clicked();

private:
    Ui::DutyAdd *ui;

    DutyEntity *entity;
    int mid = 0;
};

#endif // DUTYADD_H
