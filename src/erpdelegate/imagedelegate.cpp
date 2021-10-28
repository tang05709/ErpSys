#include "imagedelegate.h"
#include <QPainter>
#include <QPoint>
#include <QApplication>

ImageDelegate::ImageDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
      QString src = index.data(Qt::DisplayRole).toString();
      QPixmap pixmap(src);
      int width = pixmap.width();
      int height = pixmap.height();
      // 高度固定50，宽度计算 width/height = x/50
      int scaledWidth = width * 50 / height;
      QPixmap showPix = pixmap.scaled(scaledWidth, 50);
      painter->drawPixmap(QRect(option.rect.left() + 2, option.rect.top() + 2, scaledWidth, 50), pixmap);
}
