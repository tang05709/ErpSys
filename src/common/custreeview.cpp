#include "custreeview.h"

CusTreeView::CusTreeView() : QStandardItem()
{

}

CusTreeView::CusTreeView(const QString& text) : QStandardItem(text)
{

}

void CusTreeView::setId(int id)
{
    ID = id;
}

int CusTreeView::getId() const
{
    return ID;
}
