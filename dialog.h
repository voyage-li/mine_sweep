#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QDebug>
#include<QMessageBox>
extern int ROW,COLUMN,BOOM_NUM;
extern void begin();
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);

    ~Dialog();
private:
    Ui::Dialog *ui;
private slots:
    void getRowCol();
};

#endif // DIALOG_H
