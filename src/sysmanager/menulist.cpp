#include "menulist.h"
#include "ui_menulist.h"

MenuList::MenuList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuList)
{
    ui->setupUi(this);
    initTable();
}

MenuList::~MenuList()
{
    delete ui;
}

void MenuList::initTable()
{
    MenuModel *menuModel = new MenuModel;
    menuModel->fields("id, pid, name, created_at");
    list = menuModel->getTableList();
    list->setHeaderData(0, Qt::Horizontal, "ID");
    list->setHeaderData(1, Qt::Horizontal, "上级");
    list->setHeaderData(2, Qt::Horizontal, "名称");
    list->setHeaderData(3, Qt::Horizontal, "添加时间");
    ui->viewList->setModel(list);
}
