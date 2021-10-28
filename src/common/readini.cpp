#include "readini.h"
#include <QSettings>

ReadIni::ReadIni()
{

}

QMap<QString, QString> ReadIni::getMySqlIni()
{
    QSettings set("F:/work/qtpro/erpsys/ErpSys/config/config.ini", QSettings::IniFormat);

    set.beginGroup("mysql");
    QMap<QString, QString> config;
    config.insert("host", set.value("host").toString());
    config.insert("dbname", set.value("dbname").toString());
    config.insert("dbuser", set.value("dbuser").toString());
    config.insert("dbpassword", set.value("dbpassword").toString());
    config.insert("dbport", set.value("dbport").toString());
    set.endGroup();

    return config;
}


QMap<QString, QString> ReadIni::getOssIni()
{
    QSettings set("F:/work/qtpro/erpsys/ErpSys/config/config.ini", QSettings::IniFormat);

    set.beginGroup("oss");
    QMap<QString, QString> config;
    config.insert("accessKeyId", set.value("accessKeyId").toString());
    config.insert("accessKeySecret", set.value("accessKeySecret").toString());
    config.insert("endpoint", set.value("endpoint").toString());
    config.insert("bucketName", set.value("").toString());
    set.endGroup();

    return config;
}
