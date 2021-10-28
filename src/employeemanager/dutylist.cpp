#include "dutylist.h"
#include "ui_dutylist.h"
#include <QMessageBox>

DutyList::DutyList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DutyList)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    entity = new DutyEntity;
    initTable();
}

DutyList::~DutyList()
{
    delete ui;
}

void DutyList::initTable()
{
    all = entity->getAll();


    ui->dutyList->verticalHeader()->hide();
    ui->dutyList->horizontalHeader()->setStretchLastSection(true);
    ui->dutyList->setAlternatingRowColors(true);
    ui->dutyList->setModel(all);
    ui->dutyList->setColumnWidth(0, 60);

    tableEditAndDeleteDelegate = new TableEditAndDeleteDelegate(this);
    ui->dutyList->setItemDelegateForColumn(4, tableEditAndDeleteDelegate);
    connect(tableEditAndDeleteDelegate, SIGNAL(editData(const QModelIndex&)), this, SLOT(editData(const QModelIndex&)));
    connect(tableEditAndDeleteDelegate, SIGNAL(deleteData(const QModelIndex&)), this, SLOT(deleteData(const QModelIndex&)));

}

void DutyList::editData(const QModelIndex& index)
{

    QModelIndex idx = index.model()->index(index.row(), 1);
    int id = index.model()->data(idx).toInt();
    DutyAdd *edit = new DutyAdd(this, id);
    if (edit->exec() == QDialog::Accepted) {
        // 刷新表格
        initTable();
    }
}

void DutyList::deleteData(const QModelIndex& index)
{
    int curRow = index.row();
    all->removeRow(curRow);
    if (all->submit()) {
        initTable();
    } else {
        QMessageBox::information(this, "提示", "删除失败");
    }
}

void DutyList::on_btnAdd_clicked()
{
    DutyAdd *add = new DutyAdd(this);
    //add->exec();
    if (add->exec() == QDialog::Accepted) {
        // 刷新表格
        initTable();
    }
}
