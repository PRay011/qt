#include "socket.h"

Socket::Socket(QObject *parent) : QObject(parent)
{
    sock = new QTcpSocket(this);
    QString leip = "127.0.0.1";
    QString leport ="1123";
    sock->connectToHost(leip,leport.toInt());
    //槽函数连接
    connect(sock,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
}

void Socket::sendMessage(QByteArray dataArray)
{
    sock->write(dataArray);
}


void Socket::LoginMessage(QString str)
{
    if(str=="LoginTrue")
    {
        emit LoginSock();
    }
}

void Socket::EnrollMessage(QString str)
{

    if(str=="true")
    {
        emit EnrollSock();
    }
    else {
        QMessageBox::warning(nullptr,"","注册失败");
    }
}

void Socket::receiveMessage()
{
    QString strName,str,type,strEnroll;
    QByteArray buffer = sock->readAll();
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(buffer, &json_error);  // 转化为 JSON 文档
    if(!document.isNull() &&(json_error.error == QJsonParseError::NoError)){
        if (document.isObject()) { // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            if (object.contains("Name")) {  // 包含指定的 key
                QJsonValue value = object.value("Name");  // 获取相应的value
                strName = value.toString();  // 将 value 转化为字符串
            }
            if (object.contains("Res")) {  // 包含指定的 key
                QJsonValue value = object.value("Res");  // 获取相应的value
                str = value.toString();  // 将 value 转化为字符串
            }
            if (object.contains("Type")) {  // 包含指定的 key
                QJsonValue value = object.value("Type");  // 获取相应的value
                type = value.toString();  // 将 value 转化为字符串
            }
            if(object.contains("Enrollsuccess"))
            {
                QJsonValue value = object.value("Enrollsuccess");  // 获取相应的value
                strEnroll = value.toString();  // 将 value 转化为字符串
            }
        }
    }
    if(strName=="Login")
    {
        LoginMessage(str);
    }
    if(strName=="Enroll")
    {
        EnrollMessage(strEnroll);
    }
    if(strName=="Fruit")
    {
        if(type=="Find")
            emit FruitMessage(buffer);
        else if(type=="Search")
            emit FruitSearch(buffer);
    }
    if(strName=="Ordering")
    {
        if(type=="Find")
            emit OrderMessage(buffer);
        else if(type=="Search")
            emit OrderSearch(buffer);
    }
    if(strName=="Self")
    {
        if(type=="Find")
            emit SelfMessage(buffer);
    }
    if(strName=="Notice")
    {
        if(type=="Find")
            emit NoticeMessage(buffer);
    }
    if(strName=="Chat")
    {
        if(type=="Send")
            emit ChatMessage(buffer);
        else if(type =="ID")
            emit ChatIDMessage(buffer);
    }
}
