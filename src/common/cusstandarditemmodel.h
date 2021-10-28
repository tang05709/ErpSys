#ifndef CUSSTANDARDITEMMODEL_H
#define CUSSTANDARDITEMMODEL_H

#include <QStandardItem>
class CusStandardItemModel : public QStandardItem
{
public:
    CusStandardItemModel();
    CusStandardItemModel(const QString& text);
    ~CusStandardItemModel() {}
    void setId(int id);
    int getId() const;

private:
    int ID;
};

#endif // CUSSTANDARDITEMMODEL_H
