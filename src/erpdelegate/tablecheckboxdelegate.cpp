#include "tablecheckboxdelegate.h"
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

TableCheckBoxDelegate::TableCheckBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , idCheckbox(new QCheckBox)
{

}


TableCheckBoxDelegate::~TableCheckBoxDelegate()
{
    delete idCheckbox;
}

void TableCheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);
    if (option.state.testFlag(QStyle::State_HasFocus))
       viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

    QStyledItemDelegate::paint(painter, viewOption, index);

    // 是否选中
    bool data = index.model()->data(index, Qt::UserRole).toBool();
    idCheckbox->setChecked(data);

    // 绘制矩形区域
    QStyleOptionButton checkBoxStyle;
    //checkBoxStyle.state = data ? QStyle::State_On : QStyle::State_Off;
    checkBoxStyle.state = QStyle::State_On;
    checkBoxStyle.state |= QStyle::State_Enabled;
    checkBoxStyle.rect = QRect(option.rect.left() + 10, option.rect.top() + 2, 18, 18);


    //QApplication::style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &checkBoxStyle, painter, &checkBox2);

    QApplication::style()->drawControl(QStyle::CE_PushButton, &checkBoxStyle, painter, idCheckbox);
}

bool TableCheckBoxDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QRect decorationRect = option.rect;

    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if (event->type() == QEvent::MouseButtonPress && decorationRect.contains(mouseEvent->pos()))
    {
        bool data = model->data(index, Qt::DisplayRole).toBool();
        qDebug() << data;
        model->setData(index, true, Qt::EditRole);
    }
    qDebug() << model->data(index, Qt::DisplayRole).toBool();
     return QStyledItemDelegate::editorEvent(event, model, option, index);

}
