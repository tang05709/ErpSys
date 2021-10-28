#include "dutyadd.h"
#include "ui_dutyadd.h"
#include <QMessageBox>

DutyAdd::DutyAdd(QWidget *parent, int id) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::DutyAdd),
    mid(id)
{
    ui->setupUi(this);
    this->setProperty("class", "formclass");
    entity = new DutyEntity;
    initForm();
}

DutyAdd::~DutyAdd()
{
    delete ui;
}

void DutyAdd::initForm()
{
    if (mid > 0) {
        QMap<QString, QVariant> data = entity->getOne(mid);
        ui->leName->setText(data.value("name").toString());
    }
}

void DutyAdd::on_btnFormSubmit_clicked()
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

void DutyAdd::on_btnFormClose_clicked()
{
    this->reject();
}
