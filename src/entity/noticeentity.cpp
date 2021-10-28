#include "noticeentity.h"

NoticeEntity::NoticeEntity() : Entity("erp_notices"), mtable("erp_notices")
{

}

ErpSqlTableModel* NoticeEntity::getPage(int page, int pageSize)
{
    this->fields("id, title, status, created_at");
    this->orderBy("id DESC");
    if (page > 0) {
        this->limit(page, pageSize);
    }
    QString sql = this->joinSqlStrForQueryModel();
    pageList = new ErpSqlTableModel;

    pageList->setTable(mtable);
    pageList->setSql(sql);
    //pageList->disabledCheckbox();
    pageList->select();

    pageList->setHeaderData(1, Qt::Horizontal, "ID");
    pageList->setHeaderData(2, Qt::Horizontal, "标题");
    pageList->setHeaderData(3, Qt::Horizontal, "状态");
    pageList->setHeaderData(4, Qt::Horizontal, "添加时间");

    pageList->insertColumn(0);
    pageList->setHeaderData(0, Qt::Horizontal, "");
    pageList->insertColumn(5);
    pageList->setHeaderData(5, Qt::Horizontal, "操作");
    return pageList;
}

ErpSqlTableModel* NoticeEntity::getPage(QString condition, int page, int pageSize)
{
    this->where(condition);
    return getPage(page, pageSize);
}

QMap<QString, QVariant> NoticeEntity::getOne(int id)
{
    QSqlTableModel model;
    model.setTable(mtable);
    model.setFilter(QObject::tr("id = %1").arg(id));
    model.select();
    if (model.rowCount() > 0) {
        QSqlRecord record = model.record(0);
        currentData.insert("title", record.value("title").toString());
        currentData.insert("content", record.value("content").toString());
    }
    return currentData;
}

bool NoticeEntity::insert(QMap<QString, QVariant>& data)
{
    QSqlTableModel model;
    model.setTable(mtable);
    QSqlRecord record = model.record();
    record.setValue("title", data.value("title"));
    record.setValue("content", data.value("content"));
    record.setValue("status", 0);
    record.setValue("created_at", HelpTool::getDateTime());
    record.setValue("updated_at", HelpTool::getDateTime());
    // 如果row为负数，记录将被追加到末尾
    return model.insertRecord(-1, record);
}

bool NoticeEntity::update(QMap<QString, QVariant> &data, int id)
{
    QSqlTableModel model;
    model.setTable(mtable);
    model.setFilter(QObject::tr("id = %1").arg(id));
    model.select();
    if (model.rowCount() > 0) {
        QSqlRecord record = model.record(0);
        record.setValue("title", data.value("title"));
        record.setValue("content", data.value("content"));
        record.setValue("updated_at", HelpTool::getDateTime());
        return model.setRecord(0, record);
    }
    return false;
}

bool NoticeEntity::updateStatus(int id)
{
    QSqlTableModel model;
    model.setTable(mtable);
    model.setFilter(QObject::tr("id = %1").arg(id));
    model.select();
    if (model.rowCount() > 0) {
        QSqlRecord record = model.record(0);
        int status = record.value("status").toInt() == 1 ? 0 : 1;
        record.setValue("status", status);
        record.setValue("updated_at", HelpTool::getDateTime());
        return model.setRecord(0, record);
    }
    return false;
}
