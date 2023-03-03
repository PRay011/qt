#ifndef TALK_H
#define TALK_H

#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>
#include <QString>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>

namespace Ui {
class Talk;
}

class Talk : public QWidget
{
    Q_OBJECT

public:
    explicit Talk(QWidget *parent = nullptr);
    ~Talk();

public slots:
    void receiveMessage();

signals:
    void send_sql(QByteArray dataArray);

private slots:
    void ChatOpen();
    void on_Send_clicked();
    void ReceiveAccount(QString str1,QString str2);
    void on_Clear_clicked();

private:
    Ui::Talk *ui;
    QString Account;
    QString Password;
};

#endif // TALK_H
