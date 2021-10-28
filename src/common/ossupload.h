#ifndef OSSUPLOAD_H
#define OSSUPLOAD_H
#include <QString>
#include "src/common/readini.h"

class OssUpload
{
public:
    OssUpload();
    bool ossUpload(QString filekey, QString localFile);

private:
    ReadIni *readIni;
    QString accessKeyId;
    QString accessKeySecret;
    QString endpoint;
    QString bucketName;
};

#endif // OSSUPLOAD_H
