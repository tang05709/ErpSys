#include "ossupload.h"


OssUpload::OssUpload()
{
    readIni = new ReadIni();
    QMap<QString, QString> config = readIni->getOssIni();
    accessKeyId = config.value(accessKeyId);
    accessKeySecret = config.value(accessKeySecret);
    endpoint = config.value(endpoint);
    bucketName = config.value(bucketName);
}

bool OssUpload::ossUpload(QString filekey, QString localFile)
{

    /*InitializeSdk();
    ClientConfiguration conf;
    OssClient client(endpoint.toStdString(), accessKeyId.toStdString(), accessKeySecret.toStdString(), conf);
    std::shared_ptr<std::iostream> content = std::make_shared<std::stringstream>();
    *content << "Thank you for using Alibaba Cloud Object Storage Service!";
    auto outcome = client.PutObject(bucketName.toStdString(), filekey.toStdString(), localFile.toStdString());
    //PutObjectRequest request(bucketName.toStdString(), filekey.toStdString(), content);
    //auto outcome = client.PutObject(request);


    ShutdownSdk();
    if (outcome.isSuccess()) {
       // outcome.error().Code()
       // outcome.error().Message()
       return true;
    }*/
    return false;
}
