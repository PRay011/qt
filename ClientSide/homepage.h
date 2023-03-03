#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include<QPainter>


namespace Ui {
class HomePage;
}

class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

signals:
    void HomeClosed1();//水果
    void HomeClosed2();//订单
    void HomeClosed3();//公告
    void HomeClosed4();//聊天
    void HomeClosed5();//个人

protected:
    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动




private slots:
    void HomeClose();

    void HomeOpen();

    void on_Close_clicked();

    void on_Shrink_clicked();

    void on_FruitManagementAndCategory_clicked();

    void on_OrderManagement_clicked();

    void on_Notification_clicked();

    void on_Chat_clicked();

    void on_Chat2_clicked();

    void on_FruitManagementAndCategory2_clicked();

    void on_OrderManagement2_clicked();

    void on_Notification2_clicked();

    void on_SelfCentral_clicked();


private:
    Ui::HomePage *ui;
    QPoint p;

};

#endif // HOMEPAGE_H
