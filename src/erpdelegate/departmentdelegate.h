#ifndef DEPARTMENTDELEGATE_H
#define DEPARTMENTDELEGATE_H

#include <QStyledItemDelegate>
#include <QSqlQueryModel>
#include "src/entity/departmententity.h"
class DepartmentDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    DepartmentDelegate(QObject *parent = nullptr);

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DEPARTMENTDELEGATE_H
