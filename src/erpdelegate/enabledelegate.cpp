#include "enabledelegate.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>

EnableDelegate::EnableDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void EnableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPixmap pixmap;
    pixmap.load(":/icons/icons/disable.png");
    if (index.model()->data(index, Qt::EditRole).toInt() == 1) {
        pixmap.load(":/icons/icons/disable.png");
    } else {
        pixmap.load(":/icons/icons/enable.png");
    }
    QIcon icon(pixmap);
    QStyleOptionButton* btnStatus = new QStyleOptionButton();
    btnStatus->icon = icon;
    btnStatus->state |= QStyle::State_Enabled;
    btnStatus->rect = QRect(option.rect.left() + 10, option.rect.top() + 2, 24, 24);
    QApplication::style()->drawItemPixmap(painter, btnStatus->rect, Qt::AlignCenter, pixmap);
}

bool EnableDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QRect decorationRect = option.rect;
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if (event->type() == QEvent::MouseButtonDblClick && decorationRect.contains(mouseEvent->pos()))
    {
        emit updateStatus(index);
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
