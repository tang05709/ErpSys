#include "departmentlist.h"
#include "ui_departmentlist.h"
#include <QMessageBox>

DepartmentList::DepartmentList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DepartmentList)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    entity = new DepartmentEntity;
    initTable();
}

DepartmentList::~DepartmentList()
{
    delete ui;
}

void DepartmentList::initTable()
{
    all = entity->getAll();

    ui->departmentList->verticalHeader()->hide();
    ui->departmentList->horizontalHeader()->setStretchLastSection(true);
    ui->departmentList->setAlternatingRowColors(true);
    ui->departmentList->setModel(all);
    ui->departmentList->setColumnWidth(0, 60);

    tableEditAndDeleteDelegate = new TableEditAndDeleteDelegate(this);
    ui->departmentList->setItemDelegateForColumn(4, tableEditAndDeleteDelegate);
    connect(tableEditAndDeleteDelegate, SIGNAL(editData(const QModelIndex&)), this, SLOT(editData(const QModelIndex&)));
    connect(tableEditAndDeleteDelegate, SIGNAL(deleteData(const QModelIndex&)), this, SLOT(deleteData(const QModelIndex&)));

}

void DepartmentList::editData(const QModelIndex& index)
{

    QModelIndex idx = index.model()->index(index.row(), 1);
    int id = index.model()->data(idx).toInt();
    DepartmentAdd *edit = new DepartmentAdd(this, id);
    if (edit->exec() == QDialog::Accepted) {
        // 刷新表格
        initTable();
    }
}

void DepartmentList::deleteData(const QModelIndex& index)
{
    int curRow = index.row();
    all->removeRow(curRow);
    if (all->submit()) {
        initTable();
    } else {
        QMessageBox::information(this, "提示", "删除失败");
    }
}

void DepartmentList::on_btnAdd_clicked()
{
    DepartmentAdd *add = new DepartmentAdd(this);
    //add->exec();
    if (add->exec() == QDialog::Accepted) {
        // 刷新表格
        initTable();
    }
}
