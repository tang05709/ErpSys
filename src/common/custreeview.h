#ifndef CUSTREEVIEW_H
#define CUSTREEVIEW_H

#include <QStandardItem>

class CusTreeView : public QStandardItem
{
    Q_OBJECT
public:
    CusTreeView();
    CusTreeView(const QString& text);
    ~CusTreeView() {}
    void setId(int id);
    int getId() const;

private:
    int ID;
};

#endif // CUSTREEVIEW_H
