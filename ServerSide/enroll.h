#ifndef ENROLL_H
#define ENROLL_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <qdebug.h>
#include <QString>
#include <QMessageBox>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {
class Enroll;
}

class Enroll : public QWidget
{
    Q_OBJECT

public:
    explicit Enroll(QWidget *parent = nullptr);
    ~Enroll();

protected:
   void Sendself();
    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动

signals:
    void SendAccount2(QString str1,QString str2);
    void send_infomation(QByteArray dataArray);
    void EnrollClosed();
    void HaveName(QByteArray dataArray);


private slots:
    void EnrollOpen();
    void EnrollClose();
    void EnrollTrue();

    void on_Enrollnew_clicked();

    void on_Close_clicked();

    void on_Shrink_clicked();



private:
    Ui::Enroll *ui;
    QPoint p;

};

#endif // ENROLL_H
