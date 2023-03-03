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

protected:
    void  onShow();
    //    void onConnect();
    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动

private slots:
    void FruitOpen();
    void getMessage(QByteArray q);
    void getMessageSearch(QByteArray q);

    void on_Add_clicked();

    void on_Delete_clicked();

    void on_Save_clicked();

    void on_Search_clicked();

    void on_FruitTable_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_show_clicked();

private:
    Ui::FruitManagementAndCategory *ui;
    int Column, Row;
    QList<QString> List;
    QPoint p;
};

#endif // FRUITMANAGEMENTANDCATEGORY_H
