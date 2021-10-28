#include "departmentadd.h"
#include "ui_departmentadd.h"
#include <QMessageBox>

DepartmentAdd::DepartmentAdd(QWidget *parent, int id) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::DepartmentAdd),
    mid(id)
{
    ui->setupUi(this);
    this->setProperty("class", "formclass");
    entity = new DepartmentEntity;
    initForm();
}

DepartmentAdd::~DepartmentAdd()
{
    delete ui;
}

void DepartmentAdd::initForm()
{
    if (mid > 0) {
        QMap<QString, QVariant> data = entity->getOne(mid);
        ui->leName->setText(data.value("name").toString());
    }
}

void DepartmentAdd::on_btnFormSubmit_clicked()
{
    QString name = ui->leName->text();
    QMap<QString, QVariant> data;
    data.insert("name", name);

    bool res = false;
    if (mid > 0) {
        res = entity->update(data, mid);
    } else {
        res = entity->insert(data);
    }
    if (res) {
        this->accept();
    } else {
        QMessageBox::information(this, tr("提示"), "操作失败");
    }
}

void DepartmentAdd::on_btnFormClose_clicked()
{
    this->reject();
}
