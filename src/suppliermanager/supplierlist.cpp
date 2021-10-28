#include "supplierlist.h"
#include "ui_supplierlist.h"
#include <QMessageBox>

SupplierList::SupplierList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupplierList)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    entity = new SupplierEntity;
    initTable();
}

SupplierList::~SupplierList()
{
    delete ui;
    delete entity;
    delete imageDelegate;
    delete tableEditAndDeleteDelegate;
}

void SupplierList::initTable()
{

    pageList = entity->getPage(page, pageSize);


    ui->supplierList->verticalHeader()->hide();
    ui->supplierList->verticalHeader()->setDefaultSectionSize(55);
    ui->supplierList->horizontalHeader()->setStretchLastSection(true);
    ui->supplierList->setAlternatingRowColors(true);
    ui->supplierList->setModel(pageList);
    ui->supplierList->setColumnWidth(0, 60);


    imageDelegate = new ImageDelegate(this);
    ui->supplierList->setItemDelegateForColumn(3, imageDelegate);
    tableEditAndDeleteDelegate = new TableEditAndDeleteDelegate(this);
    ui->supplierList->setItemDelegateForColumn(8, tableEditAndDeleteDelegate);
    connect(tableEditAndDeleteDelegate, SIGNAL(editData(const QModelIndex&)), this, SLOT(editData(const QModelIndex&)));
    connect(tableEditAndDeleteDelegate, SIGNAL(deleteData(const QModelIndex&)), this, SLOT(deleteData(const QModelIndex&)));

    count = entity->getCount();
    pageCount = (count + pageSize - 1) / pageSize;
    if (count > 0) {
        ui->btnPageNext->setEnabled(true);
        ui->btnPageLast->setEnabled(true);
    }
    if (page > 1) {
        ui->btnPagePrev->setEnabled(true);
        ui->btnPageFirst->setEnabled(true);
    }
}


void SupplierList::editData(const QModelIndex& index)
{

    QModelIndex idx = index.model()->index(index.row(), 1);
    int id = index.model()->data(idx).toInt();
    SupplierAdd *edit = new SupplierAdd(this, id);
    if (edit->exec() == QDialog::Accepted) {
        // 刷新表格
        initTable();
    }
}

void SupplierList::deleteData(const QModelIndex& index)
{
    int curRow = index.row();
    pageList->removeRow(curRow);
    if (pageList->submit()) {
        initTable();
    } else {
        QMessageBox::information(this, "提示", "删除失败");
    }
}


void SupplierList::on_btnAdd_clicked()
{
    SupplierAdd *add = new SupplierAdd(this);
    if (add->exec() == QDialog::Accepted) {
        // 刷新表格
        initTable();
    }
}

void SupplierList::on_btnPageLast_clicked()
{
    page = pageCount;
    initTable();
}

void SupplierList::on_btnPagePrev_clicked()
{
    if (page >1) {
        page--;
        initTable();
    }
}

void SupplierList::on_btnPageFirst_clicked()
{
    page = 1;
    initTable();
}

void SupplierList::on_btnPageNext_clicked()
{
    if (page < pageCount) {
        page++;
        initTable();
    }
}
