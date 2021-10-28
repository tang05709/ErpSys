#include "pagination.h"
#include <QHBoxLayout>

Pagination::Pagination(QWidget *parent) : QWidget(parent)
{
    // 格式 首页 上一页 1 2 3 4 5 下一页 尾页 共10页100条记录
    // 计算pageCount
    pageCount = (count + pageSize - 1) / pageSize;
    pageInfo = new QLabel(tr("共%1页%2条记录").arg(pageCount).arg(count));
    btnFirst = new QPushButton(tr("首页"));
    btnFirst->setObjectName("btnPageFirst");
    btnPrev = new QPushButton(tr("上一页"));
    btnPrev->setObjectName("btnPagePrev");
    btnNext = new QPushButton(tr("下一页"));
    btnNext->setObjectName("btnPageNext");
    btnLast = new QPushButton(tr("尾页"));
    btnLast->setObjectName("btnPageLast");

    QHBoxLayout *pageLayout = new QHBoxLayout(this);
    pageLayout->addStretch();
    pageLayout->setMargin(10);
    pageLayout->setSpacing(10);
    pageLayout->addWidget(btnFirst);
    pageLayout->addWidget(btnPrev);
    pageLayout->addWidget(btnNext);
    pageLayout->addWidget(btnLast);
    pageLayout->addWidget(pageInfo);

}
