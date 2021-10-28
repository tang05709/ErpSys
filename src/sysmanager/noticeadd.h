#ifndef NOTICEADD_H
#define NOTICEADD_H

#include <QDialog>
#include "src/entity/noticeentity.h"

namespace Ui {
class NoticeAdd;
}

class NoticeAdd : public QDialog
{
    Q_OBJECT

public:
    explicit NoticeAdd(QWidget *parent = nullptr, int id = 0);
    ~NoticeAdd();
    void initForm();

private slots:
    void on_btnFormClose_clicked();

    void on_btnFormSubmit_clicked();

private:
    Ui::NoticeAdd *ui;

    NoticeEntity *entity;
    int mid = 0;
};

#endif // NOTICEADD_H
