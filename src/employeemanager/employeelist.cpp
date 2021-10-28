#include "employeelist.h"
#include "ui_employeelist.h"
#include <QMessageBox>

EmployeeList::EmployeeList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeeList)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    entity = new EmployeeEntity;
    initTable();
}

EmployeeList::~EmployeeList()
{
    delete ui;
}


void EmployeeList::initTable()
{
    pageList = entity->getPage(page, pageSize);

    ui->employeeList->verticalHeader()->hide();
    ui->employeeList->horizontalHeader()->setStretchLastSection(true);
    ui->employeeList->setAlternatingRowColors(true);
    ui->employeeList->setModel(pageList);
    ui->employeeList->setColumnWidth(0, 60);

    departmentDelegate = new DepartmentDelegate(this);
    ui->employeeList->setItemDelegateForColumn(2, departmentDelegate);
    tableEditAndDeleteDelegate = new TableEditAndDeleteDelegate(this);
    ui->employeeList->setItemDelegateForColumn(11, tableEditAndDeleteDelegate);
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

void EmployeeList::editData(const QModelIndex& index)
{

    QModelIndex idx = index.model()->index(index.row(), 1);
    int id = index.model()->data(idx).toInt();
    EmployeeAdd *edit = new EmployeeAdd(this, id);
    if (edit->exec() == QDialog::Accepted) {
        // 刷新表格
        initTable();
    }
}

void EmployeeList::deleteData(const QModelIndex& index)
{
    int curRow = index.row();
    pageList->removeRow(curRow);
    if (pageList->submit()) {
        initTable();
    } else {
        QMessageBox::information(this, "提示", "删除失败");
    }
}

void EmployeeList::on_btnAdd_clicked()
{
    EmployeeAdd *add = new EmployeeAdd(this);
    //add->exec();
    if (add->exec() == QDialog::Accepted) {
        // 刷新表格
        initTable();
    }
}

void EmployeeList::on_btnPageFirst_clicked()
{
    page = 1;
    initTable();
}

void EmployeeList::on_btnPagePrev_clicked()
{
    if (page >1) {
        page--;
        initTable();
    }
}

void EmployeeList::on_btnPageNext_clicked()
{
    if (page < pageCount) {
        page++;
        initTable();
    }
}

void EmployeeList::on_btnPageLast_clicked()
{
    page = pageCount;
    initTable();
}
