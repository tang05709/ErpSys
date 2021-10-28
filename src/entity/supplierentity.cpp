#include "supplierentity.h"

SupplierEntity::SupplierEntity() : Entity("erp_suppliers"), mtable("erp_suppliers")
{

}

ErpSqlTableModel* SupplierEntity::getPage(int page, int pageSize)
{
    this->fields("id, name, logo, contact_name, contact_phone, address, created_at");
    if (page > 0) {
        this->limit(page, pageSize);
    }
    QString sql = this->joinSqlStrForQueryModel();
    pageList = new ErpSqlTableModel;
    pageList->setTable(mtable);
    pageList->setSql(sql);
    pageList->select();
    pageList->setHeaderData(1, Qt::Horizontal, "ID");
    pageList->setHeaderData(2, Qt::Horizontal, "名称");
    pageList->setHeaderData(3, Qt::Horizontal, "LOGO");
    pageList->setHeaderData(4, Qt::Horizontal, "联系人");
    pageList->setHeaderData(5, Qt::Horizontal, "联系电话");
    pageList->setHeaderData(6, Qt::Horizontal, "地址");
    pageList->setHeaderData(7, Qt::Horizontal, "添加时间");

    pageList->insertColumn(0);
    pageList->setHeaderData(0, Qt::Horizontal, "选择");
    pageList->insertColumn(8);
    pageList->setHeaderData(8, Qt::Horizontal, "操作");
    return pageList;
}

QMap<QString, QVariant> SupplierEntity::getOne(int id)
{
    QSqlTableModel model;
    model.setTable(mtable);
    model.setFilter(QObject::tr("id = %1").arg(id));
    model.select();
    if (model.rowCount() > 0) {
        QSqlRecord record = model.record(0);
        currentData.insert("name", record.value("name").toString());
        currentData.insert("contact_name", record.value("contact_name").toString());
        currentData.insert("contact_phone", record.value("contact_phone").toString());
        currentData.insert("address", record.value("address").toString());
        currentData.insert("logo", record.value("logo").toString());
    }
    return currentData;
}

bool SupplierEntity::insert(QMap<QString, QVariant>& data)
{
    QSqlTableModel model;
    model.setTable(mtable);
    QSqlRecord record = model.record();
    record.setValue("name", data.value("name"));
    record.setValue("contact_name", data.value("contact_name"));
    record.setValue("contact_phone", data.value("contact_phone"));
    record.setValue("address", data.value("address"));
    record.setValue("logo", data.value("logo"));
    record.setValue("created_at", HelpTool::getDateTime());
    record.setValue("updated_at", HelpTool::getDateTime());
    return model.insertRecord(-1, record);
}

bool SupplierEntity::update(QMap<QString, QVariant> &data, int id)
{
    QSqlTableModel model;
    model.setTable(mtable);
    model.setFilter(QObject::tr("id = %1").arg(id));
    model.select();
    if (model.rowCount() > 0) {
        QSqlRecord record = model.record(0);
        record.setValue("name", data.value("name"));
        record.setValue("contact_name", data.value("contact_name"));
        record.setValue("contact_phone", data.value("contact_phone"));
        record.setValue("address", data.value("address"));
        record.setValue("logo", data.value("logo"));
        record.setValue("updated_at", HelpTool::getDateTime());
        return model.setRecord(0, record);
    }
    return false;
}

