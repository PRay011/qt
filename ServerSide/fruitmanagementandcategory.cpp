#include "fruitmanagementandcategory.h"
#include "ui_fruitmanagementandcategory.h"
#include <QtDebug>
#include <QString>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QMouseEvent>

FruitManagementAndCategory::FruitManagementAndCategory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FruitManagementAndCategory)
{
    ui->setupUi(this);

}

FruitManagementAndCategory::~FruitManagementAndCategory()
{
    delete ui;
}

void FruitManagementAndCategory::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void FruitManagementAndCategory::FruitOpen()
{
    this->show();
}

void FruitManagementAndCategory::getMessage(QByteArray q)
{
    QString str;
    int a=0;
    int j=0;
    QByteArray buffer = q;
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(buffer, &json_error);  // 转化为 JSON 文档
    if(!document.isNull() &&(json_error.error == QJsonParseError::NoError)){
        if (document.isObject()) { // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            if (object.contains("Row")) {  // 包含指定的 key
                QJsonValue value = object.value("Row");  // 获取相应的value
                Row = value.toInt();  // 将 value 转化为字符串
                if(Row == -1)
                    Row = 0;
            }

            if(object.contains("Table")){
                QJsonValue TableValue = object.value("Table");
                QJsonArray TableArray = TableValue.toArray();
                ui->FruitTable->setRowCount(Row);
                Column = ui->FruitTable->columnCount();
                while(j<Row)
                {
                    for (int i = 0; i<Column; i++)
                    {
                        QJsonValue value = TableArray.at(a);
                        QString temp = value.toString();
                        ui->FruitTable->setItem(j, i, new QTableWidgetItem(temp));
                        a++;
                        if(i==0)//让编号不可修改
                            ui->FruitTable->item(j,i)->setFlags(Qt::NoItemFlags);
                    }
                    QTableWidgetItem *checkBox = new QTableWidgetItem();//添加多选框
                    checkBox->setCheckState(Qt::Unchecked);
                    ui->FruitTable->setItem(j,Column-1, checkBox);
                    j++;
                }
            }
        }
    }
}

void FruitManagementAndCategory::getMessageSearch(QByteArray q)
{
    QString str;
    int a=0;
    int j=0;
    QByteArray buffer = q;
    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(buffer, &json_error);  // 转化为 JSON 文档
    if(!document.isNull() &&(json_error.error == QJsonParseError::NoError)){
        if (document.isObject()) { // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            if (object.contains("Row")) {  // 包含指定的 key
                QJsonValue value = object.value("Row");  // 获取相应的value
                Row = value.toInt();  // 将 value 转化为字符串
            }

            if(object.contains("Table")){
                QJsonValue TableValue = object.value("Table");
                QJsonArray TableArray = TableValue.toArray();
                ui->FruitTable->setRowCount(Row);
                Column = ui->FruitTable->columnCount();
                while(j<Row)
                {
                    for (int i = 0; i<Column; i++)
                    {
                        QJsonValue value = TableArray.at(a);
                        QString temp = value.toString();
                        ui->FruitTable->setItem(j, i, new QTableWidgetItem(temp));
                        a++;
                        if(i==0)//让编号不可修改
                            ui->FruitTable->item(j,i)->setFlags(Qt::NoItemFlags);
                    }
                    QTableWidgetItem *checkBox = new QTableWidgetItem();//添加多选框
                    checkBox->setCheckState(Qt::Unchecked);
                    ui->FruitTable->setItem(j,Column-1, checkBox);
                    j++;
                }
            }
        }
    }
}

void FruitManagementAndCategory::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        //移到左上角
        move(e->globalPos() - p);
    }
}


void FruitManagementAndCategory::onShow()
{
    QString S=QString("select * from Fruit");

    QJsonObject jsonObject;
    jsonObject.insert("Name", "Fruit");
    jsonObject.insert("Type", "Find");
    jsonObject.insert("Sql", S);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray = jsonDocument.toJson();
    emit send_sql1(dataArray);

}

void FruitManagementAndCategory::on_Add_clicked()
{
    ui->FruitTable->setRowCount(Row+1);
    QTableWidgetItem *checkBox = new QTableWidgetItem();//添加多选框
    checkBox->setCheckState(Qt::Unchecked);
    ui->FruitTable->setItem(Row,Column-1, checkBox);
    QString S;

    S=QString("insert into Fruit (类别,名称,价格,销量,库存)values('%1','%2','%3','%4','%5');").arg("空").arg("空").arg("空").arg("空").arg("空");
    QJsonObject jsonObject;
    jsonObject.insert("Name", "Fruit");
    jsonObject.insert("Type", "Add");
    jsonObject.insert("Sql", S);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray = jsonDocument.toJson();
    emit send_sql1(dataArray);

}


void FruitManagementAndCategory::on_Delete_clicked()
{
    QJsonDocument jsonDocument;
    QJsonArray TableArray;
    QJsonObject jsonObject;

    int i = 0;
    while( i<Row)
    {
        if(ui->FruitTable->item(i,6)->checkState())
        {
            QString number = ui->FruitTable->item(i,0)->text();
            QString S = QString ("delete from Fruit where 编号 =%1").arg(number.toInt());
            TableArray.append(S);
        }
        i++;

    }

    jsonObject.insert("Name", "Fruit");
    jsonObject.insert("Type", "Delete");
    jsonObject.insert("Table", TableArray);
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray = jsonDocument.toJson();
    emit send_sql1(dataArray);
}

void FruitManagementAndCategory::on_Save_clicked()
{
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QJsonArray SaveArray;

    // 定义 [ ] 对象
    QJsonArray SaveArray1;
    QJsonArray SaveArray2;
    QString id,item1,item2,item3,item4,item5,item6;
    QString S1,S2;
    for(QString e:List)
    {
        id=ui->FruitTable->item(e.toInt(),0)->text();
        item1=ui->FruitTable->item(e.toInt(),1)->text();
        item2=ui->FruitTable->item(e.toInt(),2)->text();
        item3=ui->FruitTable->item(e.toInt(),3)->text();
        item4=ui->FruitTable->item(e.toInt(),4)->text();
        item5=ui->FruitTable->item(e.toInt(),5)->text();

        S1=QString("delete from Fruit where 编号='%1'").arg(id);
        SaveArray1.append(S1);

        S2=QString("insert into Fruit (类别,名称,价格,销量,库存)values('%1','%2','%3','%4','%5');").arg(item1).arg(item2).arg(item3).arg(item4).arg(item5);
        SaveArray2.append(S2);
    }
    SaveArray.append(SaveArray1);
    SaveArray.append(SaveArray2);
    jsonObject.insert("Name", "Fruit");
    jsonObject.insert("Type", "Save");
    jsonObject.insert("Table", SaveArray);
    jsonDocument.setObject(jsonObject);
    QByteArray dataArray = jsonDocument.toJson();
    emit send_sql1(dataArray);

    List.clear();
}

void FruitManagementAndCategory::on_Search_clicked()
{
    QString s = ui->Searching->text();
    if(s == "")
    {
        onShow();
    }
    else {

        QString S = QString("select * from Fruit where 名称= '%1'").arg(s);
        QJsonObject jsonObject;
        jsonObject.insert("Name", "Fruit");
        jsonObject.insert("Type", "Search");
        jsonObject.insert("Sql", S);

        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QByteArray dataArray = jsonDocument.toJson();
        emit send_sql1(dataArray);

    }
}

void FruitManagementAndCategory::on_FruitTable_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    bool temp = true;
    for(QString e:List)
    {
        if(e!=nullptr&&e.toInt()==current->row())
        {
            temp=false;
        }
    }
    if(current!=nullptr&&temp)
    {
        QString num;
        num.setNum(current->row());
        List.push_front(num) ;
    }
}

void FruitManagementAndCategory::on_show_clicked()
{
    onShow();
}
