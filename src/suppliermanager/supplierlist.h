#ifndef SUPPLIERLIST_H
#define SUPPLIERLIST_H

#include <QWidget>
#include "src/common/erpsqltablemodel.h"
#include "src/entity/supplierentity.h"
#include "src/erpdelegate/imagedelegate.h"
#include "src/erpdelegate/tableeditanddeletedelegate.h"
#include "src/suppliermanager/supplieradd.h"

namespace Ui {
class SupplierList;
}

class SupplierList : public QWidget
{
    Q_OBJECT

public:
    explicit SupplierList(QWidget *parent = nullptr);
    ~SupplierList();

    void initTable();

private slots:
    void editData(const QModelIndex& index);
    void deleteData(const QModelIndex& index);
    void on_btnAdd_clicked();

    void on_btnPageLast_clicked();

    void on_btnPagePrev_clicked();

    void on_btnPageFirst_clicked();

    void on_btnPageNext_clicked();

private:
    Ui::SupplierList *ui;

    SupplierEntity *entity;
    ErpSqlTableModel *pageList;
    ImageDelegate *imageDelegate;
    TableEditAndDeleteDelegate *tableEditAndDeleteDelegate;

    int page = 1;
    int pageSize = 20;
    int count = 0;
    int pageCount = 0;
};

#endif // SUPPLIERLIST_H
