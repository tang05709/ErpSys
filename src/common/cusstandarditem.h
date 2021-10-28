#ifndef CUSSTANDARDITEM_H
#define CUSSTANDARDITEM_H

#include <QStandardItem>
#include <QStandardItemModel>


class CusStandardItem : public QStandardItem
{
public:
    CusStandardItem();
    CusStandardItem(const QString& text);
    ~CusStandardItem() {}
    void setId(int id);
    int getId() const;

private:
    int ID;
};

#endif // CUSSTANDARDITEM_H
