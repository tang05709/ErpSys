#ifndef ERPLOGIN_H
#define ERPLOGIN_H

#include <QDialog>

namespace Ui {
class ErpLogin;
}

class ErpLogin : public QDialog
{
    Q_OBJECT

public:
    explicit ErpLogin(QWidget *parent = nullptr);
    ~ErpLogin();

private slots:
    void on_btnClose_clicked();

    void on_btnLogin_clicked();

private:
    Ui::ErpLogin *ui;
};

#endif // ERPLOGIN_H
