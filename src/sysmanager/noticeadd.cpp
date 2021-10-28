#include "noticeadd.h"
#include "ui_noticeadd.h"
#include <QMessageBox>

NoticeAdd::NoticeAdd(QWidget *parent, int id) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::NoticeAdd),
    mid(id)
{
    ui->setupUi(this);
    this->setProperty("class", "formclass");
    entity = new NoticeEntity;
    initForm();
}

NoticeAdd::~NoticeAdd()
{
    delete ui;
}

void NoticeAdd::initForm()
{
    if (mid > 0) {
        QMap<QString, QVariant> data = entity->getOne(mid);
        ui->leTitle->setText(data.value("title").toString());
        ui->teContent->setText(data.value("content").toString());
    }
}

void NoticeAdd::on_btnFormClose_clicked()
{
    this->reject();
}

void NoticeAdd::on_btnFormSubmit_clicked()
{
    QString title = ui->leTitle->text();
    QString content = ui->teContent->toPlainText();
    QMap<QString, QVariant> data;
    data.insert("title", title);
    data.insert("content", content);

    bool res = false;
    if (mid > 0) {
        res = entity->update(data, mid);
    } else {
        res = entity->insert(data);
    }

    if (res) {
        this->accept();
    } else {
        QMessageBox::information(this, tr("提示"), "添加失败");
    }
}
