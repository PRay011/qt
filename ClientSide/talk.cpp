#include "talk.h"
#include "ui_talk.h"

Talk::Talk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Talk)
{

}

Talk::~Talk()
{
    delete ui;
}

void Talk::receiveMessage()
{
    //    QByteArray arr = sock->readAll();
    //    QString str = arr.data();
    //    ui->ReceiveMessage->setText(str);
}

void Talk::ChatOpen()
{
    this->show();
}

void Talk::on_Send_clicked()
{
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;

    // 定义 [ ] 对象
    QString temp1,temp2,temp3,temp4;
    temp1 = Account;
    temp2 = "管理员";
    temp3 = QDateTime::currentDateTime().toString("yyyy年MM月dd日 hh:mm:ss");
    temp4 = ui->SendMessage->toPlainText();

    QString S = QString("insert into Fruit (发送者,接收者,时间,聊天记录)values('%1','%2','%3','%4');").arg(temp1).arg(temp2).arg(temp3).arg(temp4);

    jsonObject.insert("Name", "Chat");
    jsonObject.insert("Type", "Send");
    jsonObject.insert("Sql", S);
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray = jsonDocument.toJson();
    qDebug()<<dataArray<<"     Send";

    emit send_sql(dataArray);
}

void Talk::ReceiveAccount(QString str1,QString str2)
{
    Account = str1;
    Password = str2;
}

void Talk::on_Clear_clicked()
{
    ui->SendMessage->clear();
}

