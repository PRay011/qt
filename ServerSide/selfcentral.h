#ifndef SELFCENTRAL_H
#define SELFCENTRAL_H

#include <QWidget>
#include <QMouseEvent>//界面移动
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>


namespace Ui {
class SelfCentral;
}

class SelfCentral : public QWidget
{
    Q_OBJECT

public:
    explicit SelfCentral(QWidget *parent = nullptr);
    ~SelfCentral();

signals:
    void SelfToLogin();
    void SelfClosed3();//水果
    void SelfClosed4();//订单
    void SelfClosed5();//公告
    void send_sql3(QByteArray dataArray);

protected:
    void  onShow();

    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动

private slots:
    void SelfOpen();

    void getMessage(QByteArray q);

    void ReceiveAccount(QString str1,QString str2);//收到来自LoginPage(EnrollPage)的账号信息

    void on_FruitManagementAndCategory_clicked();

    void on_OrderManagement_clicked();

    void on_Notification_clicked();

    void on_Show_clicked();

    void on_Save_clicked();

    void on_Logout_clicked();

    void on_Close_clicked();

    void on_Shrink_clicked();

private:
    Ui::SelfCentral *ui;
    QPoint p;
    QString  passwordkeep;
};

#endif // SELFCENTRAL_H
