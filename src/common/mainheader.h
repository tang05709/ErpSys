#ifndef MAINHEADER_H
#define MAINHEADER_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>

class MainHeader : public QWidget
{
public:
    MainHeader(QWidget *parent = nullptr);
    void setUserName(const QString& userName);
    QLabel *erpWinIcon; // 系统图标
    QLabel *erpWinTitle; // 系统名称

    QLabel *user; // 登录用户
    QToolButton *erpWinLogout; // 退出登录
    QToolButton *erpWinSizeMax; // 最大化窗口
    QToolButton *erpWinSizeMin; // 最小化窗口
    QToolButton *erpWinExit; // 退出系统

};

#endif // MAINHEADER_H
