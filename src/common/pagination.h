#ifndef PAGINATION_H
#define PAGINATION_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Pagination : public QWidget
{
    Q_OBJECT
public:
    explicit Pagination(QWidget *parent = nullptr);

    int page = 1;
    int pageSize = 20;
    int count = 0;
    int pageCount = 0;
    QLabel *pageInfo;
    QPushButton *btnFirst;
    QPushButton *btnPrev;
    QPushButton *btnNext;
    QPushButton *btnLast;

};

#endif // PAGINATION_H
