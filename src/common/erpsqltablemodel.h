#ifndef ERPSQLTABLEMODEL_H
#define ERPSQLTABLEMODEL_H

#include <QSqlTableModel>
class ErpSqlTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    ErpSqlTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QString selectStatement() const override;
    void setSql(const QString& sqlstr);
    void disabledCheckbox();

public slots:
    void tableViewCheckboxChange(Qt::CheckState checkState);

private:
    QMap<int, Qt::CheckState> rowCheckMap;

    QString sql;
    bool needCheckBox = true;
};

#endif // ERPSQLTABLEMODEL_H
