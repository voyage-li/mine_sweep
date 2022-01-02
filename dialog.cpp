#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("选项");
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(getRowCol()));
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::getRowCol()
{
    bool ok;
    QString str;
    str = ui->lineEdit->text();
    ROW = str.toInt(&ok);
    if(ROW<0||ROW>80)
    {
        QMessageBox message(QMessageBox::NoIcon, "ERROR!", " ROW数据错误！");
        message.exec();
        return;
    }
    str = ui->lineEdit_2->text();
    COLUMN = str.toInt(&ok);
    if(COLUMN<0||COLUMN>50)
    {
        QMessageBox message(QMessageBox::NoIcon, "ERROR!", " COL数据错误！");
        message.exec();
        return;
    }
    str = ui->lineEdit_3->text();
    BOOM_NUM = str.toInt(&ok);
    if(BOOM_NUM>99||BOOM_NUM<=0||BOOM_NUM>ROW*COLUMN)
    {
        QMessageBox message(QMessageBox::NoIcon, "ERROR!", " 雷数不能超过99或者少于0或者大于总面积");
        message.exec();
        return;
    }
    begin();
    this->close();
}
