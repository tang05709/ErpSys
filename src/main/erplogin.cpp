#include "erplogin.h"
#include "ui_erplogin.h"
#include <QMessageBox>
#include <QFile>

ErpLogin::ErpLogin(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::ErpLogin)
{
    ui->setupUi(this);
    QString qss;
    QFile qssFile(":/stylesheet/style/login.qss");
    qssFile.open(QFile::ReadOnly);

    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        this->setStyleSheet(qss);
        qssFile.close();
    }
}

ErpLogin::~ErpLogin()
{
    delete ui;
}

void ErpLogin::on_btnClose_clicked()
{
    this->reject();
}

void ErpLogin::on_btnLogin_clicked()
{
    QString user = ui->leUser->text();
    QString pwd = ui->lePassword->text();
    if (user == "admin" && pwd == "123456") {
        this->accept();
    } else {
        ui->labError->setText("用户名或密码错误");
    }

}
