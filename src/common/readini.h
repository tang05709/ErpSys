#ifndef READINI_H
#define READINI_H
#include <QMap>

class ReadIni
{
public:
    ReadIni();
    QMap<QString, QString> getMySqlIni();
    QMap<QString, QString> getOssIni();
};

#endif // READINI_H
