#include "homepage.h"
#include "ui_homepage.h"
#include <QMouseEvent>
#include<QPushButton>


HomePage::HomePage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());


}

HomePage::~HomePage()
{
    delete ui;
}

//鼠标移动
void HomePage::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void HomePage::HomeClose()
{
    this->close();
}

void HomePage::HomeOpen()
{
    this->show();
}

void HomePage::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        //移到左上角
        move(e->globalPos() - p);
    }

}

void HomePage::on_Close_clicked()
{
    close();
}

void HomePage::on_Shrink_clicked()
{
    showMinimized();
}

void HomePage::on_FruitManagementAndCategory_clicked()
{
    emit HomeClosed1();
}


void HomePage::on_OrderManagement_clicked()
{
    emit HomeClosed2();
}

void HomePage::on_Notification_clicked()
{
    emit HomeClosed3();
}

void HomePage::on_Chat_clicked()
{
    emit HomeClosed4();
}

//点击图片（第二个跳转方式）
void HomePage::on_FruitManagementAndCategory2_clicked()
{
    emit HomeClosed1();
}

void HomePage::on_OrderManagement2_clicked()
{
    emit HomeClosed2();
}

void HomePage::on_Notification2_clicked()
{
    emit HomeClosed3();
}

void HomePage::on_Chat2_clicked()
{
    emit HomeClosed4();
}

void HomePage::on_SelfCentral_clicked()
{
    emit HomeClosed5();
}
