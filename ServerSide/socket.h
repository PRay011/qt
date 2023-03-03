#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <loginpage.h>
#include <homepage.h>
#include <fruitmanagementandcategory.h>

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr);

signals:
    //传给登陆界面
    void LoginSock();
    void EnrollSock();
    //水果页面
    void FruitMessage(QByteArray dataArray);
    void FruitSearch(QByteArray dataArray);
    //订单页面
    void OrderMessage(QByteArray dataArray);
    void OrderSearch(QByteArray dataArray);
    //个人页面
    void SelfMessage(QByteArray dataArray);
    //公告页面
    void NoticeMessage(QByteArray dataArray);
    //聊天页面
    void ChatMessage(QByteArray dataArray);
    void ChatIDMessage(QByteArray dataArray);

public slots:
    void receiveMessage();
    void sendMessage(QByteArray dataArray);
    //是否为登陆界面的信息
    void LoginMessage(QString str);

    //此为注册界面的信息
    void EnrollMessage(QString str);


private:
    QTcpSocket *sock;
    LoginPage Login;
    HomePage home;
};

#endif // SOCKET_H
