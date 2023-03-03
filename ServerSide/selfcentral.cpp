#include "selfcentral.h"
#include "ui_selfcentral.h"



SelfCentral::SelfCentral(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelfCentral)
{
    ui->setupUi(this);
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明;
    setAttribute(Qt::WA_TranslucentBackground);
}

SelfCentral::~SelfCentral()
{
    delete ui;
}

void SelfCentral::onShow()
{
    QString name = ui->Name->text();
    QString S=QString("select * from User where Name='%1'").arg(name);

    QJsonObject jsonObject;
    jsonObject.insert("Name", "Self");
    jsonObject.insert("Type", "Find");
    jsonObject.insert("Sql", S);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray = jsonDocument.toJson();
    emit send_sql3(dataArray);
}

void SelfCentral::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        //移到左上角
        move(e->globalPos() - p);
    }
}

void SelfCentral::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void SelfCentral::SelfOpen()
{
    this->show();
}

void SelfCentral::getMessage(QByteArray q)
{
    QString str;
    QByteArray buffer = q;
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(buffer, &json_error);  // 转化为 JSON 文档
    if(!document.isNull() &&(json_error.error == QJsonParseError::NoError)){
        if (document.isObject()) { // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象

            if(object.contains("Table")){
                QJsonValue TableValue = object.value("Table");
                QJsonArray TableArray = TableValue.toArray();
                QJsonValue value1 = TableArray.at(0);
                QString temp1 = value1.toString();
                ui->name->setText(temp1);
                QJsonValue value2 = TableArray.at(1);
                QString temp2 = value2.toString();
                ui->address->setText(temp2);
                QJsonValue value3 = TableArray.at(2);
                QString temp3 = value3.toString();
                ui->connect->setText(temp3);

            }
        }
    }
}

void SelfCentral::ReceiveAccount(QString str1,QString str2)
{
    ui->Name->setText(str1);
    passwordkeep = str2;
}

void SelfCentral::on_FruitManagementAndCategory_clicked()
{
    this->close();
    emit SelfClosed3();
}

void SelfCentral::on_OrderManagement_clicked()
{
    this->close();
    emit SelfClosed4();
}

void SelfCentral::on_Notification_clicked()
{
    this->close();
    emit SelfClosed5();
}



void SelfCentral::on_Show_clicked()
{
    onShow();
}

void SelfCentral::on_Save_clicked()
{
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QJsonArray SaveArray;

    // 定义 [ ] 对象
    QJsonArray SaveArray1;
    QJsonArray SaveArray2;
    QString item1,item2,item3,item4,item5;
    QString S1,S2;

    QString name = ui->Name->text();
    S1=QString("delete from User where Name='%1'").arg(name);
    SaveArray1.append(S1);

    item1 = ui->Name->text();
    item2 =  passwordkeep;
    item3 = ui->name->text();
    item4 = ui->address->text();
    item5 = ui->connect->text();
    S2=QString("insert into User (Name,Password,姓名,住址,联系方式)values('%1','%2','%3','%4','%5');").arg(item1).arg(item2).arg(item3).arg(item4).arg(item5);
    SaveArray2.append(S2);

    SaveArray.append(SaveArray1);
    SaveArray.append(SaveArray2);
    jsonObject.insert("Name", "Self");
    jsonObject.insert("Type", "Save");
    jsonObject.insert("Table", SaveArray);
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray = jsonDocument.toJson();
    emit send_sql3(dataArray);
}

void SelfCentral::on_Logout_clicked()
{
    this->close();
    emit SelfToLogin();
}


void SelfCentral::on_Close_clicked()
{
    this->close();
}

void SelfCentral::on_Shrink_clicked()
{
    this->showMinimized();
}
