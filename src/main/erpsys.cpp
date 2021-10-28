#include "erpsys.h"
#include <QStandardItem>
#include <QDateTime>
#include <QTimer>
#include <QSqlQueryModel>
#include <QFile>
#include <QMouseEvent>
#include "src/common/mainheader.h"
#include "src/entity/menuentity.h"
#include "src/rbacmanager/menulist.h"
#include "src/sysmanager/noticelist.h"
#include "src/suppliermanager/supplierlist.h"
#include "src/employeemanager/departmentlist.h"
#include "src/employeemanager/dutylist.h"
#include "src/employeemanager/employeelist.h"
#include <QDebug>

ErpSys::ErpSys(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint); // 隐藏标题栏
    this->setWindowState(Qt::WindowMaximized); // 最大化显示窗体
    loadStyle();
    initWindow();
}

ErpSys::~ErpSys()
{
}

void ErpSys::loadStyle()
{
    QString qss;
    QFile qssFile(":/stylesheet/style/main.qss");
    qssFile.open(QFile::ReadOnly);

    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        this->setStyleSheet(qss);
        qssFile.close();
    }
}

void ErpSys::initMain()
{
    // 左侧
    company = new QLabel(tr("管理系统"));
    company->setMaximumWidth(200);
    company->setMinimumHeight(60);
    company->setAlignment(Qt::AlignCenter);
    company->setObjectName("company");

    menus = new QTreeView;
    QStandardItem *rootNode = mainTreeModel.invisibleRootItem();
    MenuEntity *menuEntity = new MenuEntity;
    QSqlQueryModel *allMenu = menuEntity->getAll();

    for(int i = 0; i < allMenu->rowCount(); i++) {
        if (allMenu->record(i).value(1).toInt() == 0) {
            QStandardItem *item = new QStandardItem(allMenu->record(i).value(2).toString());
            item->setData(allMenu->record(i).value(0).toString(), Qt::UserRole);
            rootNode->appendRow(item);

            for(int j = 0; j < allMenu->rowCount(); j++) {
                if (allMenu->record(i).value(0).toInt() == allMenu->record(j).value(1).toInt()) {
                    QStandardItem *subItem = new QStandardItem(allMenu->record(j).value(2).toString());
                    subItem->setData(allMenu->record(j).value(0).toString(), Qt::UserRole);
                    item->appendRow(subItem);
                }
            }
        }
    }
    menus->setEditTriggers(QAbstractItemView::NoEditTriggers); // 不可编辑
    menus->setMaximumWidth(200); // 设置最大宽度
    menus->setHeaderHidden(true); // 隐藏头部
    menus->setObjectName("mainMenu");
    menus->setModel(&mainTreeModel);
    connect(menus, SIGNAL(clicked(QModelIndex)), SLOT(treeViewChanged(QModelIndex)));

    // 右侧
    home = new QPushButton(tr("首页"));
    home->setObjectName("homeBtn");
    curPath = new QLabel(tr(" > 欢迎"));
    home->setMaximumWidth(80);
    home->setMaximumHeight(42);
    curPath->setMaximumHeight(42);

    connect(home, SIGNAL(clicked()), this, SLOT(homeClick()));
}

void ErpSys::initFooter()
{
    copyright = new QLabel(tr("版权归科技公司所有"));
    QDateTime time = QDateTime::currentDateTime();
    curTime = new QLabel;
    curTime->setEnabled(false);
    curTime->setMaximumWidth(220);
    curTime->setMaximumHeight(42);
    curTime->setText(time.toString("yyyy-MM-dd HH:mm:ss"));
    QTimer *timer = new QTimer;
    timer->start(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateCurTime()));
}


void ErpSys::initWindow()
{
    initMain();
    initFooter();
    // 头部
    MainHeader *header = new MainHeader(this);
    connect(header->erpWinSizeMin, SIGNAL(clicked()), this, SLOT(winSizeMin()) );
    connect(header->erpWinSizeMax, SIGNAL(clicked()), this, SLOT(winSizeMax()));
    connect(header->erpWinExit, SIGNAL(clicked()), this, SLOT(winExit()));

    // 左侧
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(company);
    leftLayout->addWidget(menus);


    // 右侧路径信息
    QHBoxLayout *topPath = new QHBoxLayout;
    topPath->setAlignment(Qt::AlignRight);
    topPath->addWidget(home);
    topPath->addWidget(curPath);

    // 右侧主窗口欢迎信息
    welcome = new QLabel(tr("欢迎使用管理系统"));
    welcome->setObjectName("welcome");
    welcome->setAlignment(Qt::AlignHCenter);
    contentLayout = new QVBoxLayout;
    contentLayout->addWidget(welcome);

    // 右侧底部版权信息
    QHBoxLayout *bottomCopyright = new QHBoxLayout;
    bottomCopyright->addStretch();
    bottomCopyright->addWidget(copyright);
    bottomCopyright->addStretch();
    bottomCopyright->addWidget(curTime);


    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addLayout(topPath);
    topPath->addStretch();
    rightLayout->addLayout(contentLayout);
    topPath->addStretch();
    rightLayout->addLayout(bottomCopyright);
    rightLayout->setStretchFactor(topPath, 1);
    rightLayout->setStretchFactor(contentLayout, 2);
    rightLayout->setStretchFactor(bottomCopyright, 1);


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(leftLayout, 1);
    mainLayout->setStretchFactor(rightLayout, 2);

    QVBoxLayout *winLayout = new QVBoxLayout(this);
    winLayout->setSpacing(0);
    winLayout->setMargin(0);
    winLayout->addWidget(header);
    winLayout->addLayout(mainLayout);
    resize(800, 600);
}

void ErpSys::deleteContentLayoutWidget()
{
    QWidget *p= contentLayout->itemAt(0)->widget();
    contentLayout->removeWidget(p);
    delete p;

}

void ErpSys::treeViewChanged(QModelIndex index)
{
   deleteContentLayoutWidget();
   QStandardItem *item = mainTreeModel.itemFromIndex(index);
   int id = item->data(Qt::UserRole).toInt();

    if (id == 3) {
        NoticeList *list = new NoticeList;
        contentLayout->addWidget(list);
        curPath->setText(" > 通知");
    } else if (id == 5) {
        MenuList *list = new MenuList;
        contentLayout->addWidget(list);
        curPath->setText(" > 菜单");
    } else if (id == 24) {
        SupplierList *list = new SupplierList;
        contentLayout->addWidget(list);
        curPath->setText(" > 供应商");
    } else if (id == 29) {
        DepartmentList *list = new DepartmentList;
        contentLayout->addWidget(list);
        curPath->setText(" > 部门");
    } else if (id == 30) {
        DutyList *list = new DutyList;
        contentLayout->addWidget(list);
        curPath->setText(" > 职务");
    } else if (id == 9) {
        EmployeeList *list = new EmployeeList;
        contentLayout->addWidget(list);
        curPath->setText(" > 员工");
    } else {
        MenuList *list = new MenuList;
        contentLayout->addWidget(list);
        curPath->setText(" > 菜单");
    }
}

void ErpSys::homeClick()
{
   deleteContentLayoutWidget();

    welcome = new QLabel(tr("欢迎使用管理系统"));
    contentLayout->addWidget(welcome);
}

void ErpSys::winExit()
{
    this->close();
}

void ErpSys::winSizeMax()
{
    if (this->isMaximized()) {
        this->showNormal();
    } else {
        this->showMaximized();
    }
}

void ErpSys::winSizeMin()
{
    this->showMinimized();
}

void ErpSys::winLogout()
{

}

void ErpSys::mousePressEvent(QMouseEvent* event)
{
    // 获取到鼠标点击的位置
    erpPos = event->pos();
}
void ErpSys::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        // 获取到移动的位置与初始点击位置的距离
        QPoint diff = event->pos() - erpPos;
        // 窗口当前位置 + 移动的位置与初始点位置的距离就是新的位置
        QPoint newpos = this->pos() + diff;
        this->move(newpos);
    }
}

void ErpSys::updateCurTime()
{
    QDateTime time = QDateTime::currentDateTime();
    curTime->setText(time.toString("yyyy-MM-dd HH:mm:ss"));
}
