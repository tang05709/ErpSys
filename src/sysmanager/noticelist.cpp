#include "noticelist.h"
#include "ui_noticelist.h"
#include "noticeadd.h"
#include <QMessageBox>
#include <QDebug>


NoticeList::NoticeList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoticeList)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    entity = new NoticeEntity;
    initTable();
}

NoticeList::~NoticeList()
{
    delete ui;
}

void NoticeList::initTable()
{
    ui->leSearchTitle->setProperty("class", "searchInput");
    ui->leSearchContent->setProperty("class", "searchInput");
    headerView = new ErpTableHeaderView(Qt::Horizontal, this);
    if (condition.isEmpty()) {
        pageList = entity->getPage(page, pageSize);
    } else {
        pageList = entity->getPage(condition, page, pageSize);
    }

    ui->noticeList->setHorizontalHeader(headerView);
    connect(headerView, SIGNAL(tableViewCheckboxChange(Qt::CheckState)), pageList, SLOT(tableViewCheckboxChange(Qt::CheckState)));
    ui->noticeList->verticalHeader()->hide();
    ui->noticeList->horizontalHeader()->setStretchLastSection(true);
    ui->noticeList->setAlternatingRowColors(true);
    ui->noticeList->setModel(pageList);
    ui->noticeList->setColumnWidth(0, 60);

    enableDelegate = new EnableDelegate(this);
    ui->noticeList->setItemDelegateForColumn(3, enableDelegate);
    connect(enableDelegate, SIGNAL(updateStatus(const QModelIndex&)), this, SLOT(updateStatus(const QModelIndex&)));
    tableEditAndDeleteDelegate = new TableEditAndDeleteDelegate(this);
    ui->noticeList->setItemDelegateForColumn(5, tableEditAndDeleteDelegate);
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


void NoticeList::updateStatus(const QModelIndex& index)
{
    QModelIndex idx = index.model()->index(index.row(), 1);
    int id = index.model()->data(idx).toInt();
    if (entity->updateStatus(id)) {
        initTable();
    }
}

void NoticeList::editData(const QModelIndex& index)
{

    QModelIndex idx = index.model()->index(index.row(), 1);
    int id = index.model()->data(idx).toInt();
    NoticeAdd *edit = new NoticeAdd(this, id);
    if (edit->exec() == QDialog::Accepted) {
        // 刷新表格
        initTable();
    }
}

void NoticeList::deleteData(const QModelIndex& index)
{
    int curRow = index.row();
    pageList->removeRow(curRow);
    if (pageList->submit()) {
        initTable();
    } else {
        QMessageBox::information(this, "提示", "删除失败");
    }
}


void NoticeList::on_btnAdd_clicked()
{
    NoticeAdd *add = new NoticeAdd(this);
    //add->exec();
    if (add->exec() == QDialog::Accepted) {
        // 刷新表格
        initTable();
    }
}

void NoticeList::on_btnPageFirst_clicked()
{
    page = 1;
    initTable();
}

void NoticeList::on_btnPagePrev_clicked()
{
    if (page >1) {
        page--;
        initTable();
    }
}

void NoticeList::on_btnPageNext_clicked()
{
    if (page < pageCount) {
        page++;
        initTable();
    }
}

void NoticeList::on_btnPageLast_clicked()
{
    page = pageCount;
    initTable();
}

void NoticeList::on_btnSearch_clicked()
{
    QString title = ui->leSearchTitle->text();
    QString content = ui->leSearchContent->text();
    QVector<QString> conditions;
    if (!title.isEmpty()) {
        conditions.push_back(QString(" title like '%%1%' ").arg(title));
    }
    if (!content.isEmpty()) {
        conditions.push_back(QString(" content like '%%1%' ").arg(content));
    }
    if (!conditions.isEmpty()) {
        for(auto cnd = conditions.begin(); cnd != conditions.end(); ++cnd) {
            condition = (condition.isEmpty()) ? *cnd : "and" + *cnd;
        }
        initTable();
    }

}
