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

    //onConnect();


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
    onShow();
}

void FruitManagementAndCategory::getMessage(QByteArray q)
{
    Where.clear();
    QString str;
    int i=0;
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
                while(i<Row)
                {
                    //类别
                    j++;
                    QJsonValue value1 = TableArray.at(j);
                    QString temp1 = value1.toString();
                    Show1.append(temp1);
                    //名称
                    j++;
                    QJsonValue value2 = TableArray.at(j);
                    QString temp2 = value2.toString();
                    Show2.append(temp2);
                    //价格
                    j++;
                    QJsonValue value3 = TableArray.at(j);
                    QString temp3 = value3.toString();
                    Show3.append(temp3);
                    //销量
                    j++;
                    QJsonValue value4 = TableArray.at(j);
                    QString temp4 = value4.toString();
                    Show4.append(temp4);
                    //库存
                    j++;
                    QJsonValue value5 = TableArray.at(j);
                    QString temp5 = value5.toString();
                    Show5.append(temp5);
                    j+=2;
                    i++;
                }
            }
        }
    }
    int MAX = Show3.size();
    for(int i =0;i<MAX;i++)
    {
        Where.append(i);
    }
    //先显示第一个页面
    which = 0;
    SwichPicture(Show1.at(Where.at(which)));
    ui->Category->setText(Show1.at( Where.at(which)));
    ui->Name->setText(Show2.at( Where.at(which)));
    ui->Price->setText(Show3.at( Where.at(which)));
    ui->Sale->setText(Show4.at( Where.at(which)));
    ui->Inventory->setText(Show5.at( Where.at(which)));
}

void FruitManagementAndCategory::getMessageSearch(QByteArray q)
{
    Where.clear();
    QString str;
    int i=0;
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
                while(i<Row)
                {
                    //类别
                    j++;
                    QJsonValue value1 = TableArray.at(j);
                    QString temp1 = value1.toString();
                    Show1.append(temp1);
                    //名称
                    j++;
                    QJsonValue value2 = TableArray.at(j);
                    QString temp2 = value2.toString();
                    Show2.append(temp2);
                    //价格
                    j++;
                    QJsonValue value3 = TableArray.at(j);
                    QString temp3 = value3.toString();
                    Show3.append(temp3);
                    //销量
                    j++;
                    QJsonValue value4 = TableArray.at(j);
                    QString temp4 = value4.toString();
                    Show4.append(temp4);
                    //库存
                    j++;
                    QJsonValue value5 = TableArray.at(j);
                    QString temp5 = value5.toString();
                    Show5.append(temp5);
                    j+=2;
                    i++;
                }
            }
        }
    }

    int MAX = Show3.size();
    for(int i =0;i<MAX;i++)
    {
        Where.append(i);
    }
    //先显示第一个页面
    which = 0;
    SwichPicture(Show1.at(Where.at(which)));
    ui->Category->setText(Show1.at( Where.at(which)));
    ui->Name->setText(Show2.at( Where.at(which)));
    ui->Price->setText(Show3.at( Where.at(which)));
    ui->Sale->setText(Show4.at( Where.at(which)));
    ui->Inventory->setText(Show5.at( Where.at(which)));
}

void FruitManagementAndCategory::SwichPicture(QString category)
{
    if(category == "苹果")
    {
        ui->PictureLabel->setPixmap(QPixmap(":/Picture/apple.JPG"));
        ui->PictureLabel->setScaledContents(true);
    }
    else if(category == "梨子")
    {
        ui->PictureLabel->setPixmap(QPixmap(":/Picture/peer.JPG"));
        ui->PictureLabel->setScaledContents(true);
    }
    else if(category == "桃子")
    {
        ui->PictureLabel->setPixmap(QPixmap(":/Picture/peach.JPG"));
        ui->PictureLabel->setScaledContents(true);
    }
    else if(category =="西瓜")
    {
        ui->PictureLabel->setPixmap(QPixmap(":/Picture/watermelon.JPG"));
        ui->PictureLabel->setScaledContents(true);
    }
    else if(category == "菠萝")
    {
        ui->PictureLabel->setPixmap(QPixmap(":/Picture/pineapple.JPG"));
        ui->PictureLabel->setScaledContents(true);
    }
    else if(category == "葡萄")
    {
        ui->PictureLabel->setPixmap(QPixmap(":/Picture/grape.JPG"));
        ui->PictureLabel->setScaledContents(true);
    }
    else if(category == "榴莲")
    {
        ui->PictureLabel->setPixmap(QPixmap(":/Picture/durian.JPG"));
        ui->PictureLabel->setScaledContents(true);
    }
    else if(category == "草莓")
    {
        ui->PictureLabel->setPixmap(QPixmap(":/Picture/strawberry.JPG"));
        ui->PictureLabel->setScaledContents(true);
    }
    else if(category == "哈密瓜")
    {
        ui->PictureLabel->setPixmap(QPixmap(":/Picture/hamimelon.JPG"));
        ui->PictureLabel->setScaledContents(true);
    }
    else {
        ui->PictureLabel->setPixmap(QPixmap(":/Picture/noimage.JPG"));
        ui->PictureLabel->setScaledContents(true);
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

void FruitManagementAndCategory::on_Search_clicked()
{
    Show1.clear();
    Show2.clear();
    Show3.clear();
    Show4.clear();
    Show5.clear();
    QString s = ui->Searching->text();
    if(s == "")
    {
        onShow();
    }
    else {

        QString S = QString("select * from Fruit where 类别= '%1'").arg(s);
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

void FruitManagementAndCategory::on_PreviousPage_clicked()
{
    which--;
    if(which<0)
    {
        QMessageBox::warning(nullptr,"","已经第一页了");
        which++;
    }
    else
    {
        SwichPicture(Show1.at(Where.at(which)));
        ui->Category->setText(Show1.at(Where.at(which)));
        ui->Name->setText(Show2.at(Where.at(which)));
        ui->Price->setText(Show3.at(Where.at(which)));
        ui->Sale->setText(Show4.at(Where.at(which)));
        ui->Inventory->setText(Show5.at(Where.at(which)));
    }
}

void FruitManagementAndCategory::on_NextPage_clicked()
{
    which++;
    if(which>=Show1.size())
    {
        QMessageBox::warning(nullptr,"","已经是最后一页了");
        which--;
    }
    else
    {
        SwichPicture(Show1.at(Where.at(which)));
        ui->Category->setText(Show1.at(Where.at(which)));
        ui->Name->setText(Show2.at(Where.at(which)));
        ui->Price->setText(Show3.at(Where.at(which)));
        ui->Sale->setText(Show4.at(Where.at(which)));
        ui->Inventory->setText(Show5.at(Where.at(which)));
    }
}

void FruitManagementAndCategory::on_InPrice_clicked()
{
    Where.clear();
    int temp1,temp2;
    int MAX = Show3.size();
    for(int i =0;i<MAX;i++)
    {
        Where.append(i);
    }
    if(price){
        price =false;
        for(int i =0 ;i<MAX;i++)
        {
            for(int j =0 ;j< MAX-i-1;j++)
            {
                temp1 = Where.at(j);
                temp2 = Where.at(j+1);
                if(Show3.at(temp1)>Show3.at(temp2))
                {
                    Where.swap(j,j+1);
                }
            }
        }
    }
    else
    {
        price =true;
        for(int i =0 ;i<MAX;i++)
        {
            for(int j =0 ;j< MAX-i-1;j++)
            {
                temp1 = Where.at(j);
                temp2 = Where.at(j+1);
                if(Show3.at(temp1)<Show3.at(temp2))
                {
                    Where.swap(j,j+1);
                }
            }
        }
    }
    which =0;
    SwichPicture(Show1.at(Where.at(which)));
    ui->Category->setText(Show1.at( Where.at(which)));
    ui->Name->setText(Show2.at( Where.at(which)));
    ui->Price->setText(Show3.at( Where.at(which)));
    ui->Sale->setText(Show4.at( Where.at(which)));
    ui->Inventory->setText(Show5.at( Where.at(which)));
}

void FruitManagementAndCategory::on_InSale_clicked()
{
    Where.clear();
int temp1,temp2;
int MAX = Show4.size();
for(int i =0;i<MAX;i++)
{
    Where.append(i);
}
if(sale){
    sale =false;
    for(int i =0 ;i<MAX;i++)
    {
        for(int j =0 ;j< MAX-i-1;j++)
        {
            temp1 = Where.at(j);
            temp2 = Where.at(j+1);
            if(Show4.at(temp1)>Show4.at(temp2))
            {
                Where.swap(j,j+1);
            }
        }
    }
}
else
{
    sale =true;
    for(int i =0 ;i<MAX;i++)
    {
        for(int j =0 ;j< MAX-i-1;j++)
        {
            temp1 = Where.at(j);
            temp2 = Where.at(j+1);
            if(Show4.at(temp1)<Show4.at(temp2))
            {
                Where.swap(j,j+1);
            }
        }
    }
}

which =0;
SwichPicture(Show1.at(Where.at(which)));
ui->Category->setText(Show1.at( Where.at(which)));
ui->Name->setText(Show2.at( Where.at(which)));
ui->Price->setText(Show3.at( Where.at(which)));
ui->Sale->setText(Show4.at( Where.at(which)));
ui->Inventory->setText(Show5.at( Where.at(which)));
}

void FruitManagementAndCategory::on_InInventory_clicked()
{
Where.clear();
int temp1,temp2;
int MAX = Show5.size();
for(int i =0;i<MAX;i++)
{
    Where.append(i);
}

if(inventory){
    inventory =false;
    for(int i =0 ;i<MAX;i++)
    {
        for(int j =0 ;j< MAX-i-1;j++)
        {
            temp1 = Where.at(j);
            temp2 = Where.at(j+1);
            if(Show5.at(temp1)>Show5.at(temp2))
            {
                Where.swap(j,j+1);
            }
        }
    }
}
else
{
    inventory =true;
    for(int i =0 ;i<MAX;i++)
    {
        for(int j =0 ;j< MAX-i-1;j++)
        {
            temp1 = Where.at(j);
            temp2 = Where.at(j+1);
            if(Show5.at(temp1)<Show5.at(temp2))
            {
                Where.swap(j,j+1);
            }
        }
    }
}

which =0;
SwichPicture(Show1.at(Where.at(which)));
ui->Category->setText(Show1.at( Where.at(which)));
ui->Name->setText(Show2.at( Where.at(which)));
ui->Price->setText(Show3.at( Where.at(which)));
ui->Sale->setText(Show4.at( Where.at(which)));
ui->Inventory->setText(Show5.at( Where.at(which)));
}

void FruitManagementAndCategory::on_Picture_clicked()
{
    QString category = ui->Category->text();
    QString name = ui->Name->text();
    emit sendCategoryAndName(category,name);
}
