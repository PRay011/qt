#ifndef FRUITMANAGEMENTANDCATEGORY_H
#define FRUITMANAGEMENTANDCATEGORY_H

#include  <QWidget>
#include <QString>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <qpixmap.h>

namespace Ui {
class FruitManagementAndCategory;
}

class FruitManagementAndCategory : public QWidget
{
    Q_OBJECT

public:
    explicit FruitManagementAndCategory(QWidget *parent = nullptr);
    ~FruitManagementAndCategory();

signals:
    void send_sql1(QByteArray dataArray);
    void sendCategoryAndName(QString category,QString name);

protected:
    void  onShow();
    //    void onConnect();
    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动

private slots:
    void FruitOpen();
    void getMessage(QByteArray q);
    void getMessageSearch(QByteArray q);
    void SwichPicture(QString category);

    void on_Search_clicked();

    void on_NextPage_clicked();

    void on_PreviousPage_clicked();

    void on_InPrice_clicked();

    void on_InSale_clicked();

    void on_InInventory_clicked();

    void on_Picture_clicked();

private:
    Ui::FruitManagementAndCategory *ui;
    int Column, Row;
    QList<QString> List;
    //这里主要是二维数组不会写。。。。
    //QList<QString>ShowFiveInSeven;//每7个一个循环但只显示五个数据
    //注意上面的是第一个和最后一个不显示
    //最后决定，我直接只存入我需要的五个
    //二维不会写啊！
    QList<QString>Show1;//存类别
    QList<QString>Show2;//存名称
    QList<QString>Show3;//存价格
    QList<QString>Show4;//存销量
    QList<QString>Show5;//存库存
    bool price = true;//按价格排序
    bool sale = true;//按销量排序
    bool inventory = true;//按库存排序
    int which;//表示现在显示到了哪个界面
    QList<int>Where;//用这个进行最初始的循环
    QPoint p;
};

#endif // FRUITMANAGEMENTANDCATEGORY_H
