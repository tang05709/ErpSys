#include "menulist.h"
#include "ui_menulist.h"
#include <QDebug>

MenuList::MenuList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuList)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    entity = new MenuEntity;
    initTable();
}

MenuList::~MenuList()
{
    delete ui;
    delete entity;
}

void MenuList::initTable()
{

    list = entity->getAll();

    titles << "名称" << "操作" << "是否显示";

    treeModel.setHorizontalHeaderLabels(titles);
    QStandardItem *rootNode = treeModel.invisibleRootItem();
    list = entity->getAll();
    for(int i = 0; i < list->rowCount(); i++) {
        if (list->record(i).value(1).toInt() == 0) {
            QList<QStandardItem*> parentItem;
            QStandardItem* pName = new QStandardItem(list->record(i).value(2).toString());
            pName->setData(list->record(i).value(0).toString(), Qt::UserRole);
            QStandardItem* pPath = new QStandardItem(list->record(i).value(3).toString());
            QStandardItem* pShow = new QStandardItem("");
            parentItem.append(pName);
            parentItem.append(pPath);
            parentItem.append(pShow);
            rootNode->appendRow(parentItem);

            for(int j = 0; j < list->rowCount(); j++) {
                if (list->record(i).value(0).toInt() == list->record(j).value(1).toInt()) {
                    QList<QStandardItem*> childItem;
                    QStandardItem* cName = new QStandardItem(list->record(j).value(2).toString());
                    cName->setData(list->record(j).value(0).toString(), Qt::UserRole);
                    QStandardItem* cPath = new QStandardItem(list->record(j).value(3).toString());
                    QStandardItem* cShow = new QStandardItem("");
                    QPixmap pixmap(":/icons/icons/enable.png");
                    if (list->record(j).value(4).toInt() == 1) {
                        pixmap.load(":/icons/icons/disable.png");
                    }
                    QIcon icon(pixmap);
                    cShow->setIcon(icon);
                    childItem.append(cName);
                    childItem.append(cPath);
                    childItem.append(cShow);
                    pName->appendRow(childItem);
                }
            }
        }
    }
    ui->menuTreeList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->menuTreeList->setModel(&treeModel);
}
