#include "loginpage.h"
#include "selfcentral.h"
#include "homepage.h"
#include "socket.h"
#include "enroll.h"
#include "fruitmanagementandcategory.h"
#include "ordermanagement.h"
#include  "notification.h"
#include "chat.h"
#include <QApplication>
#include <qdebug.h>
#include <QJsonArray>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginPage l;
    Socket s;
    HomePage h;
    Enroll e;
    FruitManagementAndCategory f;
    OrderManagement o;
    SelfCentral self;
    Notification n;
    Chat c;
    l.show();

    //登陆界面到注册界面
    QObject::connect(&l, SIGNAL(LoginClosed1()), &e, SLOT(EnrollOpen()));
    QObject::connect(&l, SIGNAL(SendAccount(QString,QString)), &self, SLOT(ReceiveAccount(QString,QString)));//传递账号
    QObject::connect(&e, SIGNAL(SendAccount2(QString,QString)), &self, SLOT(ReceiveAccount(QString,QString)));//传递账号
    //传递账号到聊天页面
    QObject::connect(&e, SIGNAL(SendAccount2(QString,QString)), &c, SLOT(ReceiveAccount(QString,QString)));//注册界面
    QObject::connect(&l, SIGNAL(SendAccount(QString,QString)), &c, SLOT(ReceiveAccount(QString,QString)));//登陆界面
    //主界面到水果界面
    QObject::connect(&h, SIGNAL(HomeClosed1()), &f, SLOT(FruitOpen()));
    //主界面到订单页面
    QObject::connect(&h, SIGNAL(HomeClosed2()), &o, SLOT(OrderOpen()));
    //主界面到公告页面
    QObject::connect(&h, SIGNAL(HomeClosed3()), &n, SLOT(NoticeOpen()));
    //主界面到聊天页面
    QObject::connect(&h, SIGNAL(HomeClosed4()), &c, SLOT(ChatOpen()));
    //主页面到个人中心
    QObject::connect(&h, SIGNAL(HomeClosed5()), &self, SLOT(SelfOpen()));

    //    //个人界面到注册界面
    //    QObject::connect(&self, SIGNAL(SelfClosed1()), &e, SLOT(EnrollOpen()));
    //    QObject::connect(&self, SIGNAL(SelfClosed1()), &h, SLOT(HomeOpen()));
    //个人界面到登录界面
    QObject::connect(&self, SIGNAL(SelfToLogin()), &l, SLOT(LoginOpen()));
    QObject::connect(&self, SIGNAL(SelfToLogin()), &h, SLOT(HomeClose()));

    //个人界面到水果界面
    QObject::connect(&self, SIGNAL(SelfClosed3()), &f, SLOT(FruitOpen()));
    //个人界面到订单界面
    QObject::connect(&self, SIGNAL(SelfClosed4()), &o, SLOT(OrderOpen()));
    //个人界面到公告界面
    QObject::connect(&self, SIGNAL(SelfClosed5()), &n, SLOT(NoticeOpen()));

    //登录
    QObject::connect(&l, SIGNAL(send_sql(QByteArray)), &s, SLOT(sendMessage(QByteArray)));
    //注册
    QObject::connect(&e, SIGNAL(send_infomation(QByteArray)), &s, SLOT(sendMessage(QByteArray)));
    QObject::connect(&e, SIGNAL(HaveName(QByteArray)), &s, SLOT(sendMessage(QByteArray)));
    QObject::connect(&s, SIGNAL(EnrollSock()), &e, SLOT(EnrollTrue()));

    //水果表格
    QObject::connect(&f, SIGNAL(send_sql1(QByteArray)), &s, SLOT(sendMessage(QByteArray)));
    QObject::connect(&s, SIGNAL(FruitMessage(QByteArray)), &f, SLOT(getMessage(QByteArray)));
    QObject::connect(&s, SIGNAL(FruitSearch(QByteArray)), &f, SLOT(getMessageSearch(QByteArray)));
    //订单表格
    QObject::connect(&o, SIGNAL(send_sql2(QByteArray)), &s, SLOT(sendMessage(QByteArray)));
    QObject::connect(&s, SIGNAL(OrderMessage(QByteArray)), &o, SLOT(getMessage(QByteArray)));
    QObject::connect(&s, SIGNAL(OrderSearch(QByteArray)), &o, SLOT(getMessageSearch(QByteArray)));
    //个人中心
    QObject::connect(&self, SIGNAL(send_sql3(QByteArray)), &s, SLOT(sendMessage(QByteArray)));
    QObject::connect(&s, SIGNAL(SelfMessage(QByteArray)), &self, SLOT(getMessage(QByteArray)));
    //公告页面
    QObject::connect(&n, SIGNAL(send_sql4(QByteArray)), &s, SLOT(sendMessage(QByteArray)));
    QObject::connect(&s, SIGNAL(NoticeMessage(QByteArray)), &n, SLOT(getMessage(QByteArray)));
    //聊天页面
    QObject::connect(&c, SIGNAL(send_sql5(QByteArray)), &s, SLOT(sendMessage(QByteArray)));
    QObject::connect(&s, SIGNAL(ChatMessage(QByteArray)), &c, SLOT(ReceiveMessage(QByteArray)));
    QObject::connect(&s, SIGNAL(ChatIDMessage(QByteArray)), &c, SLOT(ReceiveIDMessage(QByteArray)));

    //登录界面到主界面（前面是发送要不要换页面），后面是换页面
    QObject::connect(&s, SIGNAL(LoginSock()), &l, SLOT(LoginClose()));
    QObject::connect(&l, SIGNAL(LoginClosed()), &h, SLOT(HomeOpen()));
    //注册界面到主界面（前面是发送要不要换页面），后面是换页面
    QObject::connect(&s, SIGNAL(EnrollSock()), &e, SLOT(EnrollClose()));
    QObject::connect(&e, SIGNAL(EnrollClosed()), &h, SLOT(HomeOpen()));



    return a.exec();
}

