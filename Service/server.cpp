#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    //开启端口服务
    listen(QHostAddress::Any,1123);
    //数据库打开
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("Users.db");
    if(!database.open())
    {
        database.close();
    }
}

void Server::incomingConnection(qintptr handle)
{
    qDebug()<<"服务器连接成功";
    QTcpSocket *socket;
    socket = new  QTcpSocket(this);
    socket->setSocketDescriptor(handle);
    //槽函数连接
    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
}

void Server::receiveMessage()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
        sock=socket;
    QString strName,str,type,str1;
    //写入读取信号
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
            if (object.contains("Sql")) {  // 包含指定的 key
                QJsonValue value = object.value("Sql");  // 获取相应的value
                str = value.toString();  // 将 value 转化为字符串
            }
            if(object.contains("Type"))
            {
                QJsonValue value = object.value("Type");  // 获取相应的value
                type = value.toString();  // 将 value 转化为字符串
            }
        }
    }
    if(strName=="Login")
    {
        LoginMessge(str);
    }
    if(strName=="Enroll")
    {
        if(type=="False")
            EnrollMessageRight(str);
        else if(type=="True")
            EnrollMessage(str);
    }
    if(strName=="Fruit")
    {
        if(type=="Find")
            FruitMessageFind(str);
        else if(type=="Add")
            FruitMessageAdd( str);
        else if(type=="Delete")
        {
            FruitMessageDelete(buffer);
        }
        else if(type=="Search")
        {
            FruitMessageSearch(str);
        }
        else if(type=="Save")
        {
            FruitMessageSave(buffer);
        }
    }
    if(strName=="Ordering")
    {
        if(type=="Find")
            OrderMessageFind(str);
        else if(type=="Add")
            OrderMessageAdd( str);
        else if(type=="Delete")
        {
            OrderMessageDelete(buffer);
        }
        else if(type=="Search")
        {
            OrderMessageSearch(str);
        }
        else if(type=="Save")
        {
            OrderMessageSave(buffer);
        }
    }
    if(strName=="Self")
    {
        if(type=="Find")
            SelfMessageFind(str);
        else if(type=="Save")
            SelfMessageSave(buffer);
    }
    if(strName=="Notice")
    {
        if(type=="Find")
            NoticeMessageFind(str);
        else if(type=="Save")
            NoticeMessageSave(str);
    }
    if(strName == "Chat")
    {
        if(type=="Send")
            ChatMessage(buffer);
        else if(type =="ID")
        {
            ChatGetId(str);
        }
    }
}

void Server::sendResult()
{

}

//注册
void Server::EnrollMessageRight(QString str)
{
    QSqlQuery query;
    query.exec(str);
    if(query.next())
    {
        QJsonObject jsonObject;
        jsonObject.insert("Name", "Enroll");
        jsonObject.insert("Enrollsuccess", "false");

        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QByteArray dataArray2 = jsonDocument.toJson();
        sock->write(dataArray2);
    }
    else
    {
        QJsonObject jsonObject;
        jsonObject.insert("Name", "Enroll");
        jsonObject.insert("Enrollsuccess", "true");

        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QByteArray dataArray2 = jsonDocument.toJson();
        sock->write(dataArray2);
    }
}

void Server::EnrollMessage(QString str)
{
    QString S;
    QSqlQuery query;
    query.exec(str);


    S="EnrollTrue";
    QJsonObject jsonObject;
    jsonObject.insert("Name", "Enroll");
    jsonObject.insert("Res", S);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray2 = jsonDocument.toJson();
}

//登录
void Server::LoginMessge(QString str)
{
    QString S;
    QSqlQuery query;
    query.exec(str);
    if(query.next())
    {
        S="LoginTrue";
        QJsonObject jsonObject;
        jsonObject.insert("Name", "Login");
        jsonObject.insert("Res", S);
        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QByteArray dataArray2 = jsonDocument.toJson();
        sock->write(dataArray2);
    }
}

//水果界面
void Server::FruitMessageFind(QString str)
{
    int i=0;
    int j=0;
    int Row;
    QSqlQuery query;
    query.exec(str);

    query.last();
    Row = query.at() + 1;
    query.first();
    QJsonObject jsonObject;
    // 定义 [ ] 对象
    QJsonArray TableArray;

    //记录每一个表格的值
    while(j<Row)
    {
        for (i = 0; i<7; i++)
        {
            TableArray.append(query.value(i).toString());
        }
        j++;
        query.next();
    }

    jsonObject.insert("Name", "Fruit");
    jsonObject.insert("Row", Row);
    jsonObject.insert("Type", "Find");
    jsonObject.insert("Table", TableArray);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray2 = jsonDocument.toJson();

    sock->write(dataArray2);
}

void Server::FruitMessageAdd(QString str)
{
    QSqlQuery query;
    query.exec(str);

}

void Server::FruitMessageDelete(QByteArray u)
{
    QString str;
    QByteArray buffer = u;
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(buffer, &json_error);  // 转化为 JSON 文档
    if(!document.isNull() &&(json_error.error == QJsonParseError::NoError)){
        if (document.isObject()) { // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            QJsonValue TableValue = object.value("Table");
            QJsonArray TableArray = TableValue.toArray();
            for (int i = 0; i < TableArray.size(); i++) {
                QJsonValue Table = TableArray.at(i);
                str = Table.toString();
                QSqlQuery query;
                query.exec(str);
            }
        }
    }
}

void Server::FruitMessageSearch(QString str)
{
    int i=0;
    int j=0;
    int Row;
    QSqlQuery query;
    query.exec(str);
    query.last();
    Row = query.at()+1;
    query.first();

    QJsonObject jsonObject;
    // 定义 [ ] 对象
    QJsonArray TableArray;

    //记录每一个表格的值
    while(j<Row)
    {
        for (i = 0; i<7; i++)
        {
            TableArray.append(query.value(i).toString());
        }
        j++;
        query.next();
    }

    jsonObject.insert("Name", "Fruit");
    jsonObject.insert("Row", Row);
    jsonObject.insert("Type", "Search");
    jsonObject.insert("Table", TableArray);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray2 = jsonDocument.toJson();

    sock->write(dataArray2);
}

void Server::FruitMessageSave(QByteArray u)
{
    QString str;
    QByteArray buffer = u;
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(buffer, &json_error);  // 转化为 JSON 文档
    if(!document.isNull() &&(json_error.error == QJsonParseError::NoError)){
        if (document.isObject()) { // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            QJsonValue SaveValue = object.value("Table");
            QJsonArray SaveArray = SaveValue.toArray();

            for (int i = 0; i < SaveArray.size(); i++) {
                QJsonValue Arr = SaveArray.at(i);
                QJsonArray EachArray = Arr.toArray();
                for(int j =0;j<EachArray.size();j++){
                    QJsonValue Content = EachArray.at(j);
                    str = Content.toString();
                    QSqlQuery query;
                    query.exec(str);
                }
            }
        }
    }
}

//订单界面
void Server::OrderMessageFind(QString str)
{
    int i=0;
    int j=0;
    int Row;
    QSqlQuery query;
    query.exec(str);


    query.last();
    Row = query.at() + 1;
    query.first();
    QJsonObject jsonObject;
    // 定义 [ ] 对象
    QJsonArray TableArray;

    //记录每一个表格的值
    while(j<Row)
    {
        for (i = 0; i<6; i++)
        {
            TableArray.append(query.value(i).toString());
        }
        j++;
        query.next();
    }

    jsonObject.insert("Name", "Ordering");
    jsonObject.insert("Row", Row);
    jsonObject.insert("Type", "Find");
    jsonObject.insert("Table", TableArray);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray2 = jsonDocument.toJson();

    sock->write(dataArray2);
}

void Server::OrderMessageAdd(QString str)
{
    QSqlQuery query;
    query.exec(str);
}

void Server::OrderMessageDelete(QByteArray u)
{
    QString str;
    QByteArray buffer = u;
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(buffer, &json_error);  // 转化为 JSON 文档
    if(!document.isNull() &&(json_error.error == QJsonParseError::NoError)){
        if (document.isObject()) { // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            QJsonValue TableValue = object.value("Table");
            QJsonArray TableArray = TableValue.toArray();
            for (int i = 0; i < TableArray.size(); i++) {
                QJsonValue Table = TableArray.at(i);
                str = Table.toString();
                QSqlQuery query;
                query.exec(str);
            }
        }
    }
}

void Server::OrderMessageSearch(QString str)
{
    int i=0;
    int j=0;
    int Row;
    QSqlQuery query;
    query.exec(str);
    query.last();
    Row = query.at()+1;
    query.first();

    QJsonObject jsonObject;
    // 定义 [ ] 对象
    QJsonArray TableArray;

    //记录每一个表格的值
    while(j<Row)
    {
        for (i = 0; i<6; i++)
        {
            TableArray.append(query.value(i).toString());
        }
        j++;
        query.next();
    }

    jsonObject.insert("Name", "Ordering");
    jsonObject.insert("Row", Row);
    jsonObject.insert("Type", "Search");
    jsonObject.insert("Table", TableArray);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray2 = jsonDocument.toJson();

    sock->write(dataArray2);
}

void Server::OrderMessageSave(QByteArray u)
{
    QString str;
    QByteArray buffer = u;
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(buffer, &json_error);  // 转化为 JSON 文档
    if(!document.isNull() &&(json_error.error == QJsonParseError::NoError)){
        if (document.isObject()) { // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            QJsonValue SaveValue = object.value("Table");
            QJsonArray SaveArray = SaveValue.toArray();

            for (int i = 0; i < SaveArray.size(); i++) {
                QJsonValue Arr = SaveArray.at(i);
                QJsonArray EachArray = Arr.toArray();
                for(int j =0;j<EachArray.size();j++){
                    QJsonValue Content = EachArray.at(j);
                    str = Content.toString();
                    QSqlQuery query;
                    query.exec(str);
                }
            }
        }
    }
}

void Server::SelfMessageFind(QString str)
{
    QSqlQuery query;
    query.exec(str);
    if(!query.next())
    {
        QMessageBox::warning(nullptr,"","无");
    }
    else{
        query.first();
        QJsonObject jsonObject;
        // 定义 [ ] 对象
        QJsonArray TableArray;

        //记录每一个表格的值

        for (int i = 2; i<5; i++)
        {
            TableArray.append(query.value(i).toString());
        }

        jsonObject.insert("Name", "Self");
        jsonObject.insert("Type", "Find");
        jsonObject.insert("Table", TableArray);

        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QByteArray dataArray2 = jsonDocument.toJson();

        sock->write(dataArray2);
    }
}

void Server::SelfMessageSave(QByteArray u)
{
    QString str;
    QByteArray buffer = u;
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(buffer, &json_error);  // 转化为 JSON 文档
    if(!document.isNull() &&(json_error.error == QJsonParseError::NoError)){
        if (document.isObject()) { // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            QJsonValue SaveValue = object.value("Table");
            QJsonArray SaveArray = SaveValue.toArray();

            for (int i = 0; i < SaveArray.size(); i++) {
                QJsonValue Arr = SaveArray.at(i);
                QJsonArray EachArray = Arr.toArray();
                for(int j =0;j<EachArray.size();j++){
                    QJsonValue Content = EachArray.at(j);
                    str = Content.toString();
                    QSqlQuery query;
                    query.exec(str);
                }
            }
        }
    }
}

void Server::NoticeMessageFind(QString str)
{
    QSqlQuery query;
    query.exec(str);
    query.first();
    QJsonObject jsonObject;
    QString S = query.value(1).toString();
    jsonObject.insert("Name", "Notice");
    jsonObject.insert("Type", "Find");
    jsonObject.insert("Res", S);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray2 = jsonDocument.toJson();
    // 定义 [ ] 对象
    sock->write(dataArray2);
}

void Server::NoticeMessageSave(QString str)
{
    QString S=QString("delete from Notice where 编号='%1'").arg(1);
    QSqlQuery query;
    query.exec(S);
    query.exec(str);
}

void Server::ChatMessage(QByteArray u)
{
    QString Account,str;
    QByteArray buffer = u;
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(buffer, &json_error);  // 转化为 JSON 文档
    if(!document.isNull() &&(json_error.error == QJsonParseError::NoError)){
        if (document.isObject()) { // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            QJsonValue SaveValue = object.value("Table");
            QJsonArray SaveArray = SaveValue.toArray();
            QJsonValue value1 = SaveArray.at(0);
            QJsonValue value2 = SaveArray.at(1);
            Account = value1.toString();
            str = value2.toString();
        }
    }
    QSqlQuery query;
    query.exec(str);
    QString S = QString("select * from Chat where 发送者 ='%1' or 接收者 = '%1'").arg(Account);
    int j=0;
    int Row;
    query.exec(S);
    if(!query.next()){
        QMessageBox::warning(nullptr,"","无");
    }
    else{
        query.last();
        Row = query.at() + 1;
        query.first();
        QJsonObject jsonObject;
        // 定义 [ ] 对象
        QJsonArray TableArray;
        QJsonArray Array1,Array2;

        //记录每一个表格的值
        while(j<Row)
        {
            TableArray.append(query.value(1).toString());
            TableArray.append(query.value(3).toString());
            TableArray.append(query.value(4).toString());
            j++;
            query.next();
        }

        jsonObject.insert("Name", "Chat");
        jsonObject.insert("Type", "Send");
        jsonObject.insert("Table", TableArray);

        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QByteArray dataArray2 = jsonDocument.toJson();

        sock->write(dataArray2);
    }
}

void Server::ChatGetId(QString str)
{
    int Row;
    int j=0;
    QSqlQuery query;
    query.exec(str);
    query.last();
    Row = query.at() + 1;
    query.first();
    QJsonObject jsonObject;
    // 定义 [ ] 对象
    QJsonArray TableArray;
    QJsonArray Array1,Array2;

    //记录每一个表格的值
    while(j<Row)
    {
        TableArray.append(query.value(0).toString());
        j++;
        query.next();
    }

    jsonObject.insert("Name", "Chat");
    jsonObject.insert("Type", "ID");
    jsonObject.insert("Table", TableArray);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray2 = jsonDocument.toJson();

    sock->write(dataArray2);
}
