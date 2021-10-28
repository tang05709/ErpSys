#ifndef SUPPLIERADD_H
#define SUPPLIERADD_H

#include <QWidget>
#include <QDialog>
#include "src/entity/supplierentity.h"
#include "src/common/helptool.h"

namespace Ui {
class SupplierAdd;
}

class SupplierAdd : public QDialog
{
    Q_OBJECT

public:
    explicit SupplierAdd(QWidget *parent = nullptr, int id = 0);
    ~SupplierAdd();

    void initForm();

private slots:
    void on_btnUpload_clicked();

    void on_btnFormClose_clicked();

    void on_btnFormSubmit_clicked();

private:
    Ui::SupplierAdd *ui;

    SupplierEntity *entity;
    QString upLogo;
    int mid = 0;
};

#endif // SUPPLIERADD_H
