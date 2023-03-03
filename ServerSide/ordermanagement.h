#ifndef ORDERMANAGEMENT_H
#define ORDERMANAGEMENT_H

#include <QWidget>
#include <QString>
#include <QTableWidgetItem>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>

namespace Ui {
class OrderManagement;
}

class OrderManagement : public QWidget
{
    Q_OBJECT



public:
    explicit OrderManagement(QWidget *parent = nullptr);
    ~OrderManagement();

signals:
    void send_sql2(QByteArray dataArray);

protected:
    void  onShow();
    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动

private slots:
    void OrderOpen();

    void getMessage(QByteArray q);
    void getMessageSearch(QByteArray q);

    void on_Add_clicked();

    void on_Delete_clicked();

    void on_Save_clicked();

    void on_Search_clicked();

    void on_show_clicked();

    void on_OrderTable_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

private:
    Ui::OrderManagement *ui;
    int Column, Row;
    QList<QString> List;
    QPoint p;
};

#endif // ORDERMANAGEMENT_H
