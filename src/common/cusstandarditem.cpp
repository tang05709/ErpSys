#include "cusstandarditem.h"

CusStandardItem::CusStandardItem() : QStandardItem()
{

}

CusStandardItem::CusStandardItem(const QString& text) : QStandardItem(text)
{

}

void CusStandardItem::setId(int id)
{
    ID = id;
}

int CusStandardItem::getId() const
{
    return ID;
}
