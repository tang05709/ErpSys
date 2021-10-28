#ifndef NOTICELIST_H
#define NOTICELIST_H

#include <QWidget>
#include "src/common/erptableheaderview.h"
#include "src/common/erpsqltablemodel.h"
#include "src/entity/noticeentity.h"
#include "src/erpdelegate/enabledelegate.h"
#include "src/erpdelegate/tableeditanddeletedelegate.h"

namespace Ui {
class NoticeList;
}

class NoticeList : public QWidget
{
    Q_OBJECT

public:
    explicit NoticeList(QWidget *parent = nullptr);
    ~NoticeList();

    void initTable();

private slots:
    void updateStatus(const QModelIndex &index);
    void editData(const QModelIndex& index);
    void deleteData(const QModelIndex& index);

    void on_btnAdd_clicked();

    void on_btnPageFirst_clicked();

    void on_btnPagePrev_clicked();

    void on_btnPageNext_clicked();

    void on_btnPageLast_clicked();

    void on_btnSearch_clicked();

private:
    Ui::NoticeList *ui;

    NoticeEntity *entity;
    ErpTableHeaderView *headerView;
    ErpSqlTableModel *pageList;
    EnableDelegate *enableDelegate;
    TableEditAndDeleteDelegate *tableEditAndDeleteDelegate;

    QString condition;
    int page = 1;
    int pageSize = 20;
    int count = 0;
    int pageCount = 0;
};

#endif // NOTICELIST_H
