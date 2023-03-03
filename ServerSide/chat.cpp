#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
}

Chat::~Chat()
{
    delete ui;
}

void Chat::ReceiveMessage(QByteArray dataArray)
{
    ui->ReceiveMessage->clear();
    QString str1,str2,str3;
    QByteArray buffer = dataArray;
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(buffer, &json_error);  // 转化为 JSON 文档
    if(!document.isNull() &&(json_error.error == QJsonParseError::NoError)){
        if (document.isObject()) { // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            QJsonValue SaveValue = object.value("Table");
            QJsonArray TableArray = SaveValue.toArray();
            for (int i = 0; i < TableArray.size(); i+=3) {
                QJsonValue Value1 = TableArray.at(i);
                QJsonValue Value2 = TableArray.at(i+1);
                QJsonValue Value3 = TableArray.at(i+2);
                str1 = Value1.toString();
                str2 = Value2.toString();
                str3 = Value3.toString();
                QString S1=QString("<font style='font-size:25px;font-family:宋体;'>%1 %2</font><br>").arg(str1).arg(str2);
                QString S2 =QString("<font style='font-size:20px;font-family:宋体;'>%1</font><br>").arg(str3);
                Content.append(S1);
                Content.append(S2);
            }
            ui->ReceiveMessage->setHtml(Content);
        }
    }
}

void Chat::ReceiveIDMessage(QByteArray dataArray)
{
    while (ui->ID->count() > 0)
    {
        Go =false;
        QListWidgetItem *item = ui->ID->takeItem(0);
        delete item;
    }
    Go = true;
    QString str;
    QByteArray buffer = dataArray;
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(buffer, &json_error);  // 转化为 JSON 文档
    if(!document.isNull() &&(json_error.error == QJsonParseError::NoError)){
        if (document.isObject()) { // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            QJsonValue SaveValue = object.value("Table");
            QJsonArray TableArray = SaveValue.toArray();
            for (int i = 0; i < TableArray.size(); i++) {
                QJsonValue Value = TableArray.at(i);
                str = Value.toString();
                QListWidgetItem *ite = new QListWidgetItem;
                ite->setText(str);
                ui->ID->addItem(ite);
            }
        }
    }
}

void Chat::ChatOpen()
{
    GetUserId();
    this->show();
}

void Chat::on_Send_clicked()
{
    Content.clear();
    ui->ReceiveMessage->clear();
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QJsonArray SaveArray;

    // 定义 [ ] 对象
    QString temp1,temp2,temp3,temp4;
    temp1 = Account;
    temp2 = Id;
    temp3 = QDateTime::currentDateTime().toString("yyyy年MM月dd日 hh:mm:ss");
    temp4 = ui->SendMessage->toPlainText();

    QString S = QString("insert into Chat (发送者,接收者,时间,聊天记录)values('%1','%2','%3','%4');").arg(temp1).arg(temp2).arg(temp3).arg(temp4);
    SaveArray.append(Account);
    SaveArray.append(S);

    jsonObject.insert("Name", "Chat");
    jsonObject.insert("Type", "Send");
    jsonObject.insert("Table", SaveArray);
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray = jsonDocument.toJson();

    emit send_sql5(dataArray);
}

void Chat::ReceiveAccount(QString str1,QString str2)
{
    Account = str1;
    Password = str2;
}

void Chat::GetUserId()
{
    QJsonObject jsonObject;
    QString S = "select * from Client";
    jsonObject.insert("Name", "Chat");
    jsonObject.insert("Type", "ID");
    jsonObject.insert("Sql", S);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray = jsonDocument.toJson();

    emit send_sql5(dataArray);
}

void Chat::on_Clear_clicked()
{
    ui->SendMessage->clear();
}

void Chat::on_ID_currentRowChanged(int currentRow)
{
    if(Go){
        Id = ui->ID->item(currentRow)->text();
        ui->SendName->setText(Id);
    }
}
