#include "notification.h"
#include "ui_notification.h"

Notification::Notification(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Notification)
{
    ui->setupUi(this);
}

Notification::~Notification()
{
    delete ui;
}

void Notification::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        //移到左上角
        move(e->globalPos() - p);
    }
}

void Notification::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void Notification::onShow()
{
    QString S=QString("select * from Notice");

    QJsonObject jsonObject;
    jsonObject.insert("Name", "Notice");
    jsonObject.insert("Type", "Find");
    jsonObject.insert("Sql", S);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray = jsonDocument.toJson();
    emit send_sql4(dataArray);
}

void Notification::getMessage(QByteArray q)
{
    QString str;
    QByteArray buffer = q;
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(buffer, &json_error);  // 转化为 JSON 文档
    if(!document.isNull() &&(json_error.error == QJsonParseError::NoError)){
        if (document.isObject()) { // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            if(object.contains("Res"))
            {
                QJsonValue Value = object.value("Res");
                QString temp = Value.toString();
                ui->Notice->setText(temp);
            }
        }
}
}
void Notification::NoticeOpen()
{
    onShow();
    this->show();
}

void Notification::on_Show_clicked()
{
    QString str = ui->Notice->toPlainText();
    QString S=QString("insert into Notice (编号,公告)values('%1','%2');").arg(1).arg(str);

    QJsonObject jsonObject;
    jsonObject.insert("Name", "Notice");
    jsonObject.insert("Type", "Save");
    jsonObject.insert("Sql", S);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray = jsonDocument.toJson();
    emit send_sql4(dataArray);
}


void Notification::on_Clear_clicked()
{
    ui->Notice->clear();
}
