#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <block.h>
#include <QTimer>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDesktopServices>
#include <dialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void dfs(int x,int y);
private slots:
    void on_secondadd();
    void on_actioneasy_triggered();
    void on_actionmeduim_triggered();
    void on_actionhard_triggered();
    void on_actiondefined_triggered();
    void on_actionnewgame_triggered();
    void on_actionwriter_triggered();
    void on_actionhelp_triggered();
private:
    Ui::MainWindow *ui;
    QTimer * runtime;
    Dialog * useDefineWindows;
};
void begin();
bool whetherwin();
void restart(int row,int col,int mine_num);
#endif // MAINWINDOW_H
