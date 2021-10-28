#ifndef ERPTABLEHEADERVIEW_H
#define ERPTABLEHEADERVIEW_H

#include <QHeaderView>

class ErpTableHeaderView : public QHeaderView
{
    Q_OBJECT

public:
    explicit ErpTableHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;
    void mousePressEvent(QMouseEvent *e) override;
signals:
    void tableViewCheckboxChange(Qt::CheckState checkState);
private:
    Qt::CheckState mChkState = Qt::Unchecked;
};

#endif // ERPTABLEHEADERVIEW_H
