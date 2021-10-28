#include "employeeadd.h"
#include "ui_employeeadd.h"
#include <QMessageBox>

EmployeeAdd::EmployeeAdd(QWidget *parent, int id) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::EmployeeAdd),
    mid(id)
{
    ui->setupUi(this);
    this->setProperty("class", "formclass");
    entity = new EmployeeEntity;

    sexGroup = new QButtonGroup(this);
    sexGroup->setExclusive(true);
    sexGroup->setObjectName("sexGroup");
    sexGroup->addButton(ui->rbSexMale);
    sexGroup->addButton(ui->reSexFemale);

    DepartmentEntity *departmentEntity = new DepartmentEntity;
    QSqlQueryModel *allDepartment = departmentEntity->getAll();
    for (int i = 0; i < allDepartment->rowCount(); ++i) {
        ui->cmbDepartment->addItem(allDepartment->record(i).value(2).toString(),
                                   allDepartment->record(i).value(1).toInt());
    }

    DutyEntity *dutyEntity = new DutyEntity;
    QSqlQueryModel *allDuties = dutyEntity->getAll();
    for (int i = 0; i < allDuties->rowCount(); ++i) {
        ui->cmbDuty->addItem(allDuties->record(i).value(2).toString(),
                                   allDuties->record(i).value(1).toInt());
    }

    initForm();
}

EmployeeAdd::~EmployeeAdd()
{
    delete ui;
}

void EmployeeAdd::initForm()
{
    if (mid > 0) {
        QMap<QString, QVariant> data = entity->getOne(mid);
        for (int i = 0; i < ui->cmbDepartment->count(); ++i) {
            if  (ui->cmbDepartment->itemData(i).toInt() == data.value("department_id").toInt()) {
                ui->cmbDepartment->setCurrentIndex(i);
            }
        }

        for (int i = 0; i < ui->cmbDuty->count(); ++i) {
            if  (ui->cmbDuty->itemData(i).toInt() == data.value("duty_id").toInt()) {
                ui->cmbDuty->setCurrentIndex(i);
            }
        }

        ui->leName->setText(data.value("name").toString());
        ui->deBirthday->setDate(data.value("birthday").toDate());
        QString sex = data.value("sex").toString();
        if (ui->rbSexMale->text() == sex) {
            ui->rbSexMale->setChecked(true);
        } else {
            ui->reSexFemale->setChecked(true);
        }
        ui->dsbHeight->setValue(data.value("height").toDouble());
        ui->dsbWeight->setValue(data.value("weight").toDouble());
        ui->cmbNation->setCurrentText(data.value("nation").toString());
    }
}

void EmployeeAdd::on_btnFormClose_clicked()
{
    this->reject();
}

void EmployeeAdd::on_btnFormSubmit_clicked()
{
    QString name = ui->leName->text();
    QString birthday = ui->deBirthday->text();
    QString sex = sexGroup->checkedButton()->text();
    double height = ui->dsbHeight->text().toDouble();
    double weight = ui->dsbWeight->text().toDouble();
    QString nation= ui->cmbNation->currentText();
    //int department_id = ui->cmbDepartment->itemData(ui->cmbDepartment->currentIndex()).toInt();
    //int duty_id = ui->cmbDuty->itemData(ui->cmbDuty->currentIndex()).toInt();
    int department_id = ui->cmbDepartment->currentData().toInt();
    int duty_id = ui->cmbDuty->currentData().toInt();

    QMap<QString, QVariant> data;
    data.insert("name", name);
    data.insert("birthday", birthday);
    data.insert("sex", sex);
    data.insert("height", height);
    data.insert("weight", weight);
    data.insert("nation", nation);
    data.insert("department_id", department_id);
    data.insert("duty_id", duty_id);

    bool res = false;
    if (mid > 0) {
        res = entity->update(data, mid);
    } else {
        res = entity->insert(data);
    }
    if (res) {
        this->accept();
    } else {
        QMessageBox::information(this, tr("提示"), "操作失败");
    }
}
