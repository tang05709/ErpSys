#ifndef TABLEEDITANDDELETEDELEGATE_H
#define TABLEEDITANDDELETEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPushButton>

class TableEditAndDeleteDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TableEditAndDeleteDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
signals:
    void editData(const QModelIndex &index);
    void deleteData(const QModelIndex &index);

private:
    typedef QMap<QModelIndex, QPair<QStyleOptionButton*, QStyleOptionButton*>* >  actionButtons;
    actionButtons btnActions;
};

#endif // TABLEEDITANDDELETEDELEGATE_H
