#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QByteArray>
#include <QJsonObject>
#include <QNetworkDatagram>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QByteArray>
#include <QMessageBox>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);


public slots:
    void incomingConnection(qintptr handle);//重写虚方法
    void receiveMessage();
    void sendResult();
    //是否为登陆界面的信息
    void LoginMessge(QString str);
    //此为注册界面的信息
    void EnrollMessageRight(QString str);
    void EnrollMessage(QString str);
    //水果界面信息
    void FruitMessageFind(QString str);
    void FruitMessageAdd(QString str);
    void FruitMessageDelete(QByteArray u);
    void FruitMessageSearch(QString str);
    void FruitMessageSave(QByteArray u);
    //订单界面
    void OrderMessageFind(QString str);
    void OrderMessageAdd(QString str);
    void OrderMessageDelete(QByteArray u);
    void OrderMessageSearch(QString str);
    void OrderMessageSave(QByteArray u);
    //个人中心
    void SelfMessageFind(QString str);
    void SelfMessageSave(QByteArray u);
    //公告界面
    void NoticeMessageFind(QString str);
    void NoticeMessageSave(QString str);
    //聊天界面
    void ChatMessage(QByteArray u);
    void ChatGetId(QString str);


private:
    QTcpSocket *sock;
    QSqlDatabase database;


};

#endif // SERVER_H
