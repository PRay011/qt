#include "enroll.h"
#include "ui_enroll.h"



Enroll::Enroll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Enroll)
{
    ui->setupUi(this);

    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //绑定回车注册
    ui->Enrollnew->setShortcut(Qt::Key_Enter);//将字母区回车键与注册按钮绑定在一起


    //onConnect();

}

Enroll::~Enroll()
{
    delete ui;
}

void Enroll::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}
void Enroll::EnrollOpen()
{
    this->show();
}

void Enroll::EnrollClose()
{
    QString str1 = ui->Account->text();
    QString str2 = ui->Password->text();
    emit SendAccount2(str1,str2);
    this->close();
    emit EnrollClosed();


}

void Enroll::EnrollTrue()
{
    QString Name = ui->Account->text();
    QString Password = ui->Password->text();
    QString S=QString("insert into Client (Name,Password,姓名,住址,联系方式)values('%1','%2','%3','%4','%5');").arg(Name).arg(Password).arg("空").arg("空").arg("空");
    //传给服务器
    QJsonObject jsonObject;
    jsonObject.insert("Name", "Enroll");
    jsonObject.insert("Type", "True");
    jsonObject.insert("Sql", S);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray = jsonDocument.toJson();
    emit send_infomation(dataArray);

    //发送到服务器
}

void Enroll::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        //移到左上角
        move(e->globalPos() - p);
    }

}

void Enroll::on_Enrollnew_clicked()
{
    QString Name = ui->Account->text();
    QString Password = ui->Password->text();

    if(Name == "")
        QMessageBox::warning(nullptr,"","用户名不能为空！");
    else if(Password == "")
        QMessageBox::warning(nullptr,"","密码不能为空！");
    else
    {
        QString S1=QString("select * from Client where Name ='%1'").arg(Name);
        //传给服务器
        QJsonObject jsonObject1;
        jsonObject1.insert("Name", "Enroll");
        jsonObject1.insert("Type", "False");
        jsonObject1.insert("Sql", S1);

        QJsonDocument jsonDocument1;
        jsonDocument1.setObject(jsonObject1);
        QByteArray dataArray1 = jsonDocument1.toJson();
        emit HaveName(dataArray1);
    }

}

void Enroll::on_Close_clicked()
{
    this->close();
}

void Enroll::on_Shrink_clicked()
{
    this->showMinimized();
}

