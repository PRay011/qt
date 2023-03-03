#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <server.h>
#include <QTcpServer>
#include <QMessageBox>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:


private:
    Ui::Widget *ui;
    Server server;

};

#endif // WIDGET_H
