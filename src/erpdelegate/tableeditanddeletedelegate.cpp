#include "tableeditanddeletedelegate.h"
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QDebug>

TableEditAndDeleteDelegate::TableEditAndDeleteDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}


void TableEditAndDeleteDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPair<QStyleOptionButton*, QStyleOptionButton*>* buttons = btnActions.value(index);

    if (!buttons) {
        QStyleOptionButton* btnEdit = new QStyleOptionButton();
        btnEdit->text = "编辑";
        btnEdit->state |= QStyle::State_Enabled;
        btnEdit->rect = QRect(option.rect.left() + 10, option.rect.top() + 2, 50, 25);

        QStyleOptionButton* btnDelete = new QStyleOptionButton();
        btnDelete->text = "删除";
        btnDelete->state |= QStyle::State_Enabled;
        btnDelete->rect = QRect(option.rect.left() + 80, option.rect.top() + 2, 50, 25);
        buttons =new  QPair<QStyleOptionButton*, QStyleOptionButton*>(btnEdit, btnDelete);
        (const_cast<TableEditAndDeleteDelegate *>(this))->btnActions.insert(index, buttons);
    }

    QPushButton btnEdit;
    btnEdit.setStyleSheet("QPushButton{border: none; border-radius: 3px; \
                             padding: 8px 15px; color: #000000; \
                             background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #5c60e3, stop:1 #4e9eda);}");
    btnEdit.style()->drawControl(QStyle::CE_PushButton, buttons->first, painter, &btnEdit);

    QPushButton btnDelete;
    btnDelete.setStyleSheet("QPushButton{border: none; border-radius: 3px; padding: 8px 15px; \
                            color: #000000; background: #ec6f22;}");
    btnDelete.style()->drawControl(QStyle::CE_PushButton, buttons->second, painter, &btnDelete);
}

bool TableEditAndDeleteDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *pEvent = static_cast<QMouseEvent *> (event);
        if (btnActions.contains(index)) {
            QPair<QStyleOptionButton*, QStyleOptionButton*>* btns = btnActions.value(index);
            if (btns->first->rect.contains(pEvent->x(), pEvent->y())) {
                emit editData(index);
                return  true;
            } else if(btns->second->rect.contains(pEvent->x(), pEvent->y())) {
                emit deleteData(index);
                return  true;
            }
        }

    }
    return false;
}

QSize TableEditAndDeleteDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setWidth(100);
    return size;
}

