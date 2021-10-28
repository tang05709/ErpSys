#include "mainheader.h"
#include <QHBoxLayout>
#include <QVariant>

MainHeader::MainHeader(QWidget *parent) : QWidget(parent)
{
    erpWinIcon = new QLabel;
    QPixmap icon(":/images/images/erplogo.jpg");
    QPixmap fixIcon = icon.scaled(16, 16, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    erpWinIcon->setPixmap(fixIcon);
    erpWinTitle = new QLabel("ErpSystem");

    erpWinLogout = new QToolButton;
    erpWinLogout->setIcon(QIcon(":/icons/icons/exit.png"));
    erpWinLogout->setStyleSheet("background: transparent;");
    erpWinSizeMin = new QToolButton;
    erpWinSizeMin->setIcon(QIcon(":/icons/icons/winmin.png"));
    erpWinSizeMin->setStyleSheet("background: transparent;");
    erpWinSizeMax = new QToolButton;
    erpWinSizeMax->setIcon(QIcon(":/icons/icons/winmax.png"));
    erpWinSizeMax->setStyleSheet("background: transparent;");
    erpWinExit = new QToolButton;
    erpWinExit->setIcon(QIcon(":/icons/icons/close.png"));
    erpWinExit->setStyleSheet("background: transparent;");

    user = new QLabel(tr("admin"));

    QHBoxLayout *headerLayout = new QHBoxLayout(this);
    headerLayout->addWidget(erpWinIcon);
    headerLayout->addWidget(erpWinTitle);
    headerLayout->addStretch();
    headerLayout->addWidget(user);
    headerLayout->addWidget(erpWinLogout);
    headerLayout->addWidget(erpWinSizeMin);
    headerLayout->addWidget(erpWinSizeMax);
    headerLayout->addWidget(erpWinExit);

    this->setStyleSheet("background: #1c1b2d; border-bottom: 1px solid #1c1b2d;");
}

void MainHeader::setUserName(const QString& userName)
{
    user->setText(userName);
}
