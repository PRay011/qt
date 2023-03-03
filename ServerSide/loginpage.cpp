#include "loginpage.h"
#include "ui_loginpage.h"

LoginPage::LoginPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明;
    setAttribute(Qt::WA_TranslucentBackground);
    //绑定回车登录
    ui->Login->setShortcut(Qt::Key_Enter);//将字母区回车键与登录按钮绑定在一起


    //建立并打开数据库

    //    onConnect();


}

LoginPage::~LoginPage()
{
    delete ui;
}

//界面拖动
void LoginPage::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void LoginPage::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        //移到左上角
        move(e->globalPos() - p);
    }
}

void LoginPage::LoginOpen()
{
    this->show();
}

void LoginPage::LoginClose()
{
    this->close();
    emit LoginClosed();
    QString str1 = ui->Account->text();
    QString str2 = ui->Password->text();
    emit SendAccount(str1,str2);
}



//退出
void LoginPage::on_Close_clicked()
{
    close();
}

//缩小到任务栏
void LoginPage::on_Shrink_clicked()
{
    showMinimized();
}

void LoginPage::on_Login_clicked()
{
    QString Name=ui->Account->text();
    QString Password=ui->Password->text();
    QString S=QString("select * from User where Name ='%1' and Password = '%2'").arg(Name).arg(Password);

    QJsonObject jsonObject;
    jsonObject.insert("Name", "Login");
    jsonObject.insert("Sql", S);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray = jsonDocument.toJson();
    emit send_sql(dataArray);

}

void LoginPage::on_Enroll_clicked()
{
    this->close();
    emit LoginClosed1();
}

