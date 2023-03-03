#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QStyleOption>
#include <QMouseEvent>//界面移动
#include <QtWidgets/QApplication>
#include <qdebug.h>
#include <QMessageBox>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT


public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

protected:

    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动

signals:
    void SendAccount(QString str1,QString str2);
    void send_sql(QByteArray dataArray);
    void LoginClosed();
    void LoginClosed1();


private slots:
    void LoginOpen();
    void LoginClose();

    void on_Close_clicked();

    void on_Shrink_clicked();

    void on_LogIn_clicked();

    void on_Enroll_clicked();

private:
    Ui::Login *ui;
    QPoint p;


};
#endif // LOGIN_H
