#ifndef DUTYLIST_H
#define DUTYLIST_H

#include <QWidget>
#include "src/common/erpsqltablemodel.h"
#include "src/entity/dutyentity.h"
#include "src/employeemanager/dutyadd.h"
#include "src/erpdelegate/tableeditanddeletedelegate.h"

namespace Ui {
class DutyList;
}

class DutyList : public QWidget
{
    Q_OBJECT

public:
    explicit DutyList(QWidget *parent = nullptr);
    ~DutyList();
    void initTable();

private slots:
    void editData(const QModelIndex& index);
    void deleteData(const QModelIndex& index);
    void on_btnAdd_clicked();

private:
    Ui::DutyList *ui;

    DutyEntity *entity;
    ErpSqlTableModel *all;
    TableEditAndDeleteDelegate *tableEditAndDeleteDelegate;
};

#endif // DUTYLIST_H
