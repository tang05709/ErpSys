#ifndef HELPTOOL_H
#define HELPTOOL_H

#include <QString>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QCryptographicHash>
#include <QDebug>

class HelpTool
{
public:
    HelpTool();

    const static QString getDate() {
        return QDate::currentDate().toString("yyyy-MM-dd");
    }
    const static QString getTime() {
        return QTime::currentTime().toString("hh:mm:ss");
    }
    const static QString getDateTime() {
         return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    }

    const static QString getDateTimeStr() {
        return QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
    }

    const static QString getRandomStr(int len) {
        qsrand(QDateTime::currentMSecsSinceEpoch());
        char str[len];
        int i;
        for (i = 0; i < len; ++i) {
            switch (rand() %3) {
            case 1:
                str[i] = 'A' + rand() % 26;
                break;
            case 2:
                str[i] = 'a' + rand() % 26;
                break;
            default:
                str[i] = '0' + rand() % 10;
                break;
            }
        }
        return str;
    }

    const static QString getFileKey(const QString& ext) {
        QString newFileName = getDateTimeStr() +  getRandomStr(12) + "." + ext;
        return "erp/" + getDate() + "/" + newFileName;
    }

    const static QString md5Str(QString& str, QString& salt) {
        QString strMd5;
        QByteArray qba;
        qba = QCryptographicHash::hash((str + salt).toLatin1(), QCryptographicHash::Md5);
        strMd5.append(qba.toHex());
        return strMd5;
    }

};

#endif // HELPTOOL_H
