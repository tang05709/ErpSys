#ifndef TABLECHECKBOXDELEGATE_H
#define TABLECHECKBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QCheckBox>
class TableCheckBoxDelegate : public  QStyledItemDelegate
{
    Q_OBJECT
public:
    TableCheckBoxDelegate(QObject *parent = nullptr);
     ~TableCheckBoxDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;


private:
    QCheckBox *idCheckbox;
};

#endif // TABLECHECKBOXDELEGATE_H
