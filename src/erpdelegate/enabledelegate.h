#ifndef ENABLEDELEGATE_H
#define ENABLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPushButton>

class EnableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit EnableDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
    void updateStatus(const QModelIndex &index);

private:
    QStyleOptionButton *btnStatus;
};

#endif // ENABLEDELEGATE_H
