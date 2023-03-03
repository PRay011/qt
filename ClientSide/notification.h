#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QWidget>
#include <QMouseEvent>//界面移动
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>

namespace Ui {
class Notification;
}

class Notification : public QWidget
{
    Q_OBJECT

public:
    explicit Notification(QWidget *parent = nullptr);
    ~Notification();

protected:

    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动

signals:
        void send_sql4(QByteArray dataArray);

protected:
    void  onShow();

private slots:

    void getMessage(QByteArray q);
    void NoticeOpen();
    //公告的修改与发布功能已被禁用
    //void on_Show_clicked();

  //  void on_Clear_clicked();

private:
    Ui::Notification *ui;
    QPoint p;
};

#endif // NOTIFICATION_H
