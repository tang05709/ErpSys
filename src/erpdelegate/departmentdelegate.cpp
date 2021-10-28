#include "departmentdelegate.h"
#include <QComboBox>
#include <QDebug>

DepartmentDelegate::DepartmentDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget * DepartmentDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    DepartmentEntity *departmentEntity = new DepartmentEntity;
    QSqlQueryModel *allDepartment = departmentEntity->getAll();
    for(int i = 0; i < allDepartment->rowCount(); ++i) {
        editor->addItem(allDepartment->record(i).value(2).toString(), allDepartment->record(i).value(1).toInt());
    }
    editor->installEventFilter(const_cast<DepartmentDelegate*>(this));
    return editor;
}

void DepartmentDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int id = index.data().toInt();
    QComboBox *box = static_cast<QComboBox*>(editor);
    int i =box->findData(id);
    box->setCurrentIndex(i);
}

void DepartmentDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *box = static_cast<QComboBox*>(editor);
    QString str = box->currentText();
    model->setData(index, str);
}

void DepartmentDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
