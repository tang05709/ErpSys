#include "menuentity.h"

MenuEntity::MenuEntity() : Entity("erp_menus"), mtable("erp_menus")
{

}


QSqlQueryModel* MenuEntity::getAll()
{
    this->fields("id, pid, name, class_path, not_show, created_at");
    QString sql = this->joinSqlStrForQueryModel();
    allList = new QSqlQueryModel;
    allList->setQuery(sql);
    allList->setHeaderData(0, Qt::Horizontal, "ID");
    allList->setHeaderData(1, Qt::Horizontal, "上级");
    allList->setHeaderData(2, Qt::Horizontal, "名称");
    allList->setHeaderData(3, Qt::Horizontal, "路径");
    allList->setHeaderData(4, Qt::Horizontal, "是否显示");
    allList->setHeaderData(5, Qt::Horizontal, "添加时间");


    return allList;
}
