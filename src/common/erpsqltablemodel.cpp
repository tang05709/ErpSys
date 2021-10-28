#include "erpsqltablemodel.h"
#include <QDebug>
#define CHECK_BOX_COLUMN 0

ErpSqlTableModel::ErpSqlTableModel(QObject *parent, QSqlDatabase db) : QSqlTableModel(parent, db)
{

}

void ErpSqlTableModel::disabledCheckbox()
{
    needCheckBox = false;
}

bool ErpSqlTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if (!index.isValid())
          return false;

    if (needCheckBox) {
        int actionColumn = index.column();
        if (actionColumn == CHECK_BOX_COLUMN && role == Qt::CheckStateRole) {
            rowCheckMap[index.row()] = value.toInt() == Qt::Checked ? Qt::Checked : Qt::Unchecked;
            // The dataChanged() signal should be emitted if the data was successfully set.
            emit dataChanged(index, index);
        }
    }

    return true;
}

QVariant ErpSqlTableModel::data(const QModelIndex &idx, int role) const
{

    if (!idx.isValid())
          return QVariant();

    if (needCheckBox) {
        int actionColumn = idx.column();
        if (actionColumn == CHECK_BOX_COLUMN && role == Qt::CheckStateRole) {
            return rowCheckMap[idx.row()] == Qt::Checked ? Qt::Checked : Qt::Unchecked;
        }
    }

    return QSqlTableModel::data(idx, role);
}

Qt::ItemFlags ErpSqlTableModel::flags(const QModelIndex &index) const
{

    Qt::ItemFlags flags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    if (needCheckBox) {
        if (index.column() == CHECK_BOX_COLUMN) {
            flags |= Qt::ItemIsUserCheckable;
        }
    }

    return flags;
}

QString ErpSqlTableModel::selectStatement() const
{
    if (!sql.isEmpty()) {
        return sql;
    }
    return QSqlTableModel::selectStatement();
}

void ErpSqlTableModel::setSql(const QString& sqlstr)
{
    sql = sqlstr;
}

void ErpSqlTableModel::tableViewCheckboxChange(Qt::CheckState checkState)
{
    qDebug() << checkState;
    for (int i = 0; i < rowCount(); ++i) {
        QModelIndex idx = index(i, CHECK_BOX_COLUMN);
        setData(idx, checkState, Qt::CheckStateRole);
    }
}
