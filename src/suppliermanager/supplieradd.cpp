#include "supplieradd.h"
#include "ui_supplieradd.h"
#include <QFileDialog>
#include <QFileInfo>
#include <algorithm>
#include <QMessageBox>
#include <QBuffer>
#include <QDebug>

SupplierAdd::SupplierAdd(QWidget *parent, int id) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::SupplierAdd),
    mid(id)
{
    ui->setupUi(this);
    this->setProperty("class", "formclass");
    ui->btnUpload->setProperty("class", "btnUpload");
    entity = new SupplierEntity;
    initForm();
}

SupplierAdd::~SupplierAdd()
{
    delete ui;
    delete entity;
}

void SupplierAdd::initForm()
{
    if (mid > 0) {
        QMap<QString, QVariant> data = entity->getOne(mid);
        ui->leName->setText(data.value("name").toString());
        ui->leContactName->setText(data.value("contact_name").toString());
        ui->leContactPhone->setText(data.value("contact_phone").toString());
        ui->leAddress->setText(data.value("address").toString());
        upLogo = data.value("logo").toString();
    }
}

void SupplierAdd::on_btnUpload_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择图片", ".", "Image Files(*.jpg *.jpeg *.png)");
    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);

        QString ext = fileInfo.suffix();
        QVector<QString> exts = {"jpg", "jpeg", "png"};
        const QString *pos = std::find(exts.cbegin(), exts.cend(), ext);
        QString str = HelpTool::getRandomStr(12);
        if (pos != exts.end()) {

            QPixmap pixmap(fileName);
            QString filekey = HelpTool::getRandomStr(20);
            filekey = filekey + "." + ext;
            //QString fileKey = HelpTool::getFileKey(ext); // oss预留
            pixmap.save(filekey);

            upLogo = filekey;
        }
    }
}

void SupplierAdd::on_btnFormClose_clicked()
{
    this->reject();
}

void SupplierAdd::on_btnFormSubmit_clicked()
{
    QString name = ui->leName->text();
    QString contactName = ui->leContactName->text();
    QString contactPhone = ui->leContactPhone->text();
    QString address = ui->leAddress->text();
    QMap<QString, QVariant> data;
    data.insert("name", name);
    data.insert("contact_name", contactName);
    data.insert("contact_phone", contactPhone);
    data.insert("address", address);
    data.insert("logo", upLogo);

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
