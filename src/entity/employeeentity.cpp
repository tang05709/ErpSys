#include "employeeentity.h"

EmployeeEntity::EmployeeEntity() : Entity("erp_employees"), mtable("erp_employees")
{

}


ErpSqlTableModel* EmployeeEntity::getPage(int page, int pageSize)
{
    // select a.id, a.department_id, a.duty_id, a.name, a.birthday, a.sex, a.height,
    // a.weight, a.nation,b.name as dutyName, c.name as departmentName from erp_employees as a
    // left join erp_duties as b on a.duty_id = b.id
    // left join erp_departments as c on a.department_id = c.id;
    QString fields = "erp_employees.id, erp_departments.name as departmentName, erp_duties.name as dutyName, "
                     "erp_employees.name, erp_employees.birthday, erp_employees.sex, erp_employees.height, "
                     "erp_employees.weight, erp_employees.nation, erp_employees.created_at";
    this->fields(fields);
    this->leftJoin("erp_departments", "erp_departments.id", "erp_employees.department_id");
    this->leftJoin("erp_duties", "erp_duties.id", "erp_employees.duty_id");
    this->orderBy("erp_employees.id DESC");
    if (page > 0) {
        this->limit(page, pageSize);
    }
    QString sql = this->joinSqlStrForQueryModel();
    pageList = new ErpSqlTableModel;
    pageList->setTable(mtable);
    pageList->setSql(sql);
    pageList->select();
    pageList->setHeaderData(1, Qt::Horizontal, "ID");
    pageList->setHeaderData(2, Qt::Horizontal, "部门");
    pageList->setHeaderData(3, Qt::Horizontal, "职务");
    pageList->setHeaderData(4, Qt::Horizontal, "姓名");
    pageList->setHeaderData(5, Qt::Horizontal, "生日");
    pageList->setHeaderData(6, Qt::Horizontal, "性别");
    pageList->setHeaderData(7, Qt::Horizontal, "身高");
    pageList->setHeaderData(8, Qt::Horizontal, "体重");
    pageList->setHeaderData(9, Qt::Horizontal, "民族");
    pageList->setHeaderData(10, Qt::Horizontal, "添加时间");

    pageList->insertColumn(0);
    pageList->setHeaderData(0, Qt::Horizontal, "选择");
    pageList->insertColumn(11);
    pageList->setHeaderData(11, Qt::Horizontal, "操作");
    return pageList;
}

QMap<QString, QVariant> EmployeeEntity::getOne(int id)
{
    QSqlTableModel model;
    model.setTable(mtable);
    model.setFilter(QObject::tr("id = %1").arg(id));
    model.select();
    if (model.rowCount() > 0) {
        QSqlRecord record = model.record(0);
        currentData.insert("department_id", record.value("department_id").toInt());
        currentData.insert("duty_id", record.value("duty_id").toInt());
        currentData.insert("name", record.value("name").toString());
        currentData.insert("birthday", record.value("birthday").toDate());
        currentData.insert("sex", record.value("sex").toString());
        currentData.insert("height", record.value("height").toDouble());
        currentData.insert("weight", record.value("weight").toDouble());
        currentData.insert("nation", record.value("nation").toString());
    }
    return currentData;
}

bool EmployeeEntity::insert(QMap<QString, QVariant>& data)
{
    QSqlTableModel model;
    model.setTable(mtable);
    QSqlRecord record = model.record();
    record.setValue("department_id", data.value("department_id"));
    record.setValue("duty_id", data.value("duty_id"));
    record.setValue("name", data.value("name"));
    record.setValue("birthday", data.value("birthday"));
    record.setValue("sex", data.value("sex"));
    record.setValue("height", data.value("height"));
    record.setValue("weight", data.value("weight"));
    record.setValue("nation", data.value("nation"));
    record.setValue("created_at", HelpTool::getDateTime());
    record.setValue("updated_at", HelpTool::getDateTime());
    return model.insertRecord(-1, record);
}

bool EmployeeEntity::update(QMap<QString, QVariant> &data, int id)
{
    QSqlTableModel model;
    model.setTable(mtable);
    model.setFilter(QObject::tr("id = %1").arg(id));
    model.select();
    if (model.rowCount() > 0) {
        QSqlRecord record = model.record(0);
        record.setValue("department_id", data.value("department_id"));
        record.setValue("duty_id", data.value("duty_id"));
        record.setValue("name", data.value("name"));
        record.setValue("birthday", data.value("birthday"));
        record.setValue("sex", data.value("sex"));
        record.setValue("height", data.value("height"));
        record.setValue("weight", data.value("weight"));
        record.setValue("nation", data.value("nation"));
        record.setValue("updated_at", HelpTool::getDateTime());
        return model.setRecord(0, record);
    }
    return false;
}
