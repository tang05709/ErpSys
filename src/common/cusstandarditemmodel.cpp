#include "cusstandarditemmodel.h"

CusStandardItemModel::CusStandardItemModel() : QStandardItem()
{

}

CusStandardItemModel::CusStandardItemModel(const QString& text) : QStandardItem(text)
{

}

void CusStandardItemModel::setId(int id)
{
    ID = id;
}

int CusStandardItemModel::getId() const
{
    return ID;
}
