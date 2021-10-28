#include "src/main/erpsys.h"
#include "src/main/erplogin.h"

#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*ErpLogin erpLogin;
    if (erpLogin.exec() == QDialog::Accepted) {
        QPixmap pixmap(":/images/images/splash.jpg");
        QSplashScreen splash(pixmap);
        splash.show();
        a.processEvents();// 使程序在显示启动画面的同时仍能相应苏表等事件
        ErpSys w;
        w.show();
        splash.finish(&w); // 表示在主窗体对象初始化完成后，结束启动画面
        return a.exec();
    } else {
        return 0;
    }*/

    ErpSys w;
    w.show();
    return a.exec();
}
