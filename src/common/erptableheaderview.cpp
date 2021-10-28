#include "erptableheaderview.h"
#include <QPainter>
#include <QCheckBox>
#include <QMouseEvent>

ErpTableHeaderView::ErpTableHeaderView(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent)
{
}

void ErpTableHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();
    if (logicalIndex == 0) {
        QStyleOptionButton chkButton;
        chkButton.state |= QStyle::State_Enabled;
        chkButton.rect = QRect(rect.left() + 5, rect.top() + 5, 25, 25);
        chkButton.state |= mChkState == Qt::Unchecked ? QStyle::State_Off : QStyle::State_On;

        QCheckBox chkbox;
        // 使用option指定的样式选项，使用提供的油漆器绘制给定的原始元素
        style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &chkButton, painter, &chkbox);
        // 使用提供的油漆器绘制给定元素，并使用选项指定的样式选项
        //chkbox.style()->drawControl(QStyle::CE_CheckBox, &chkButton, painter, &chkbox);
    }
}

void ErpTableHeaderView::mousePressEvent(QMouseEvent *e)
{
    int column = logicalIndexAt(e->pos());
    if (column == 0) {
        mChkState = mChkState == Qt::Unchecked ? Qt::Checked : Qt::Unchecked;
        emit tableViewCheckboxChange(mChkState);
        this->update();
    }

    QHeaderView::mouseReleaseEvent(e);
}
