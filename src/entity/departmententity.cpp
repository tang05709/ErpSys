#include "departmententity.h"
DepartmentEntity::DepartmentEntity() : Entity("erp_departments"), mtable("erp_departments")
{

}

ErpSqlTableModel* DepartmentEntity::getAll()
{
    this->fields("id, name, created_at");
    QString sql = this->joinSqlStrForQueryModel();
    all = new ErpSqlTableModel;
    all->setTable(mtable);
    all->setSql(sql);
    all->select();
    all->setHeaderData(1, Qt::Horizontal, "ID");
    all->setHeaderData(2, Qt::Horizontal, "名称");
    all->setHeaderData(3, Qt::Horizontal, "添加时间");

    all->insertColumn(0);
    all->setHeaderData(0, Qt::Horizontal, "选择");
    all->insertColumn(4);
    all->setHeaderData(4, Qt::Horizontal, "操作");
    return all;
}

QMap<QString, QVariant> DepartmentEntity::getOne(int id)
{
    QSqlTableModel model;
    model.setTable(mtable);
    model.setFilter(QObject::tr("id = %1").arg(id));
    model.select();
    if (model.rowCount() > 0) {
        QSqlRecord record = model.record(0);
        currentData.insert("name", record.value("name").toString());
    }
    return currentData;
}

bool DepartmentEntity::insert(QMap<QString, QVariant>& data)
{
    QSqlTableModel model;
    model.setTable(mtable);
    QSqlRecord record = model.record();
    record.setValue("name", data.value("name"));
    record.setValue("created_at", HelpTool::getDateTime());
    record.setValue("updated_at", HelpTool::getDateTime());
    return model.insertRecord(-1, record);
}


bool DepartmentEntity::update(QMap<QString, QVariant> &data, int id)
{
    QSqlTableModel model;
    model.setTable(mtable);
    model.setFilter(QObject::tr("id = %1").arg(id));
    model.select();
    if (model.rowCount() > 0) {
        QSqlRecord record = model.record(0);
        record.setValue("name", data.value("name"));
        record.setValue("updated_at", HelpTool::getDateTime());
        return model.setRecord(0, record);
    }
    return false;
}
