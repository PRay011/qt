#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>
#include <QString>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>
#include <QListWidget>

namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = nullptr);
    ~Chat();


signals:
    void send_sql5(QByteArray dataArray);

private slots:
    void ChatOpen();
    void GetUserId();//获取用户id
    void ReceiveIDMessage(QByteArray dataArray);
    void ReceiveMessage(QByteArray dataArray);
    void on_Send_clicked();
    void ReceiveAccount(QString str1,QString str2);
    void on_Clear_clicked();

    void on_ID_currentRowChanged(int currentRow);

private:
    Ui::Chat *ui;
    QString Account;
    QString Password;
    QString Content;
    QString Id;
    bool Go;
};

#endif // CHAT_H
