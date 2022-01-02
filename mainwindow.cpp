#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow * tmp;
QPainter * paintmywindow;
QMap<int,QPixmap> map;
int ROW =9;
int COLUMN =9;
int BOOM_NUM = 10;
const int BLOCK_WIDTH=30;
const int BLOCK_HEIGHT=30;
const int MENU_WIDTH=26+40;
block * mine = new block(ROW,COLUMN,BOOM_NUM);

bool gameover=false;
int alreadyflag=0;
int gamestart=1;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    tmp = this;
    ui->setupUi(this);
    this->setWindowTitle("扫雷");
    this->setFixedSize(mine->getwid(),mine->geth());
    QPixmap boom(":/image/boom.bmp");
    QPixmap redflag(":/image/redflag.bmp");
    QPixmap blk_0(":/image/block_open.bmp");
    QPixmap blk_1(":/image/blk1.bmp");
    QPixmap blk_2(":/image/blk2.bmp");
    QPixmap blk_3(":/image/blk3.bmp");
    QPixmap blk_4(":/image/blk4.bmp");
    QPixmap blk_5(":/image/blk5.bmp");
    QPixmap blk_6(":/image/blk6.bmp");
    QPixmap blk_7(":/image/blk7.bmp");
    QPixmap blk_8(":/image/blk8.bmp");
    QPixmap unopen(":/image/block_close.bmp");
    QPixmap falseclick(":/image/clickboom.bmp");
    QPixmap falseflag(":/image/keilboom.bmp");
    map.insert(0,blk_0);//没有0
    map.insert(1,blk_1);
    map.insert(2,blk_2);
    map.insert(3,blk_3);
    map.insert(4,blk_4);
    map.insert(5,blk_5);
    map.insert(6,blk_6);
    map.insert(7,blk_7);
    map.insert(8,blk_8);
    map.insert(88,boom);//炸弹88
    map.insert(-1,redflag);//旗子-1
    map.insert(777,unopen);//没开的777
    map.insert(-88,falseclick);//点错了-88
    map.insert(-777,falseflag);//插错旗子-777
    runtime = new QTimer(this);
    connect(runtime,SIGNAL(timeout()),this,SLOT(on_secondadd()));
    connect(runtime,SIGNAL(timeout()),this,SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    QPixmap mine_title(":/image/mine_title.bmp");
    mine_title = mine_title.scaled(QSize(mine->getwid(),40));
    painter.drawPixmap(0,MENU_WIDTH-40,mine_title);

    QPixmap qq_smile(":/image/smile.bmp");
    QPixmap qq_lose(":/image/lose.bmp");
    QPixmap qq_proud(":/image/proud.bmp");

    if(gameover==false)
        painter.drawPixmap((int)mine->getwid()/2-11,7+MENU_WIDTH-40,qq_smile);
    if(whetherwin())
        painter.drawPixmap((int)mine->getwid()/2-11,7+MENU_WIDTH-40,qq_proud);
    else if(gameover==true)
        painter.drawPixmap((int)mine->getwid()/2-11,7+MENU_WIDTH-40,qq_lose);

    QPixmap ele_0(":/image/ele0.bmp");
    QPixmap ele_1(":/image/ele1.bmp");
    QPixmap ele_2(":/image/ele2.bmp");
    QPixmap ele_3(":/image/ele3.bmp");
    QPixmap ele_4(":/image/ele4.bmp");
    QPixmap ele_5(":/image/ele5.bmp");
    QPixmap ele_6(":/image/ele6.bmp");
    QPixmap ele_7(":/image/ele7.bmp");
    QPixmap ele_8(":/image/ele8.bmp");
    QPixmap ele_9(":/image/ele9.bmp");
    QPixmap ele_10(":/image/ele10.bmp");

    int temp_flag=mine->getboom()-alreadyflag;
    if(temp_flag<0)
    {
        painter.drawPixmap((int)((float)(mine->getwid()*36)/200)-30,5+MENU_WIDTH-40,ele_10);
        temp_flag=-temp_flag;
    }
    else
        painter.drawPixmap((int)((float)(mine->getwid()*36)/200)-30,5+MENU_WIDTH-40,ele_0);
    switch(temp_flag/10)
    {
        case 0:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)-10,5+MENU_WIDTH-40,ele_0);break;
        case 1:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)-10,5+MENU_WIDTH-40,ele_1);break;
        case 2:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)-10,5+MENU_WIDTH-40,ele_2);break;
        case 3:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)-10,5+MENU_WIDTH-40,ele_3);break;
        case 4:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)-10,5+MENU_WIDTH-40,ele_4);break;
        case 5:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)-10,5+MENU_WIDTH-40,ele_5);break;
        case 6:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)-10,5+MENU_WIDTH-40,ele_6);break;
        case 7:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)-10,5+MENU_WIDTH-40,ele_7);break;
        case 8:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)-10,5+MENU_WIDTH-40,ele_8);break;
        case 9:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)-10,5+MENU_WIDTH-40,ele_9);break;
    }
    switch(temp_flag%10)
    {
        case 0:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)+10,5+MENU_WIDTH-40,ele_0);break;
        case 1:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)+10,5+MENU_WIDTH-40,ele_1);break;
        case 2:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)+10,5+MENU_WIDTH-40,ele_2);break;
        case 3:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)+10,5+MENU_WIDTH-40,ele_3);break;
        case 4:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)+10,5+MENU_WIDTH-40,ele_4);break;
        case 5:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)+10,5+MENU_WIDTH-40,ele_5);break;
        case 6:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)+10,5+MENU_WIDTH-40,ele_6);break;
        case 7:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)+10,5+MENU_WIDTH-40,ele_7);break;
        case 8:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)+10,5+MENU_WIDTH-40,ele_8);break;
        case 9:  painter.drawPixmap((int)((float)(mine->getwid()*36)/200)+10,5+MENU_WIDTH-40,ele_9);break;
    }

    int timenum = mine->gettime();
    if(timenum>999)
        timenum=999;
    switch  (timenum/100)
    {
        case 0:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-30,5+MENU_WIDTH-40,ele_0);break;
        case 1:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-30,5+MENU_WIDTH-40,ele_1);break;
        case 2:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-30,5+MENU_WIDTH-40,ele_2);break;
        case 3:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-30,5+MENU_WIDTH-40,ele_3);break;
        case 4:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-30,5+MENU_WIDTH-40,ele_4);break;
        case 5:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-30,5+MENU_WIDTH-40,ele_5);break;
        case 6:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-30,5+MENU_WIDTH-40,ele_6);break;
        case 7:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-30,5+MENU_WIDTH-40,ele_7);break;
        case 8:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-30,5+MENU_WIDTH-40,ele_8);break;
        case 9:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-30,5+MENU_WIDTH-40,ele_9);break;
    }
    timenum%=100;
    switch  (timenum/10)
    {
        case 0:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-10,5+MENU_WIDTH-40,ele_0);break;
        case 1:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-10,5+MENU_WIDTH-40,ele_1);break;
        case 2:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-10,5+MENU_WIDTH-40,ele_2);break;
        case 3:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-10,5+MENU_WIDTH-40,ele_3);break;
        case 4:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-10,5+MENU_WIDTH-40,ele_4);break;
        case 5:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-10,5+MENU_WIDTH-40,ele_5);break;
        case 6:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-10,5+MENU_WIDTH-40,ele_6);break;
        case 7:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-10,5+MENU_WIDTH-40,ele_7);break;
        case 8:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-10,5+MENU_WIDTH-40,ele_8);break;
        case 9:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)-10,5+MENU_WIDTH-40,ele_9);break;
    }
    switch  (timenum%10)
    {
        case 0:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)+10,5+MENU_WIDTH-40,ele_0);break;
        case 1:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)+10,5+MENU_WIDTH-40,ele_1);break;
        case 2:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)+10,5+MENU_WIDTH-40,ele_2);break;
        case 3:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)+10,5+MENU_WIDTH-40,ele_3);break;
        case 4:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)+10,5+MENU_WIDTH-40,ele_4);break;
        case 5:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)+10,5+MENU_WIDTH-40,ele_5);break;
        case 6:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)+10,5+MENU_WIDTH-40,ele_6);break;
        case 7:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)+10,5+MENU_WIDTH-40,ele_7);break;
        case 8:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)+10,5+MENU_WIDTH-40,ele_8);break;
        case 9:  painter.drawPixmap((int)((float)(mine->getwid()*164)/200)+10,5+MENU_WIDTH-40,ele_9);break;
    }

    for(int i=0;i<mine->getrow();i++)
    {
        for(int j=0;j<mine->getcolumn();j++)
            painter.drawPixmap(i*BLOCK_HEIGHT,MENU_WIDTH+j*BLOCK_WIDTH,(!gameover)?map[mine->view[i][j]]:map[mine->gamedata[i][j]],0,0,BLOCK_WIDTH,BLOCK_HEIGHT);

    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(event->y()<MENU_WIDTH)
    {
        if(event->x()>(int)mine->getwid()/2-11&&event->x()<(int)mine->getwid()/2-11+25)
        {
            restart(mine->getrow(),mine->getcolumn(),mine->getboom());
            runtime->stop();
            gamestart=1;
            alreadyflag=0;
            gameover=false;
            update();
            return;
        }
        else
            return;
    }
    if(gamestart==1&&gameover==false)
    {
        runtime->start(1000);
        gamestart=0;
    }
    int x=event->x()/BLOCK_WIDTH;
    int y=(event->y()-MENU_WIDTH)/BLOCK_HEIGHT;

    if(event->button()==Qt::LeftButton&&mine->view[x][y]==777&&gameover==false)
    {
        if(mine->gamedata[x][y]==88)
        {
            gameover=true;
            runtime->stop();
            gamestart=1;
            alreadyflag=0;
            mine->gamedata[x][y]=-88;
            for(int i=0;i<mine->getrow();i++)
                for(int j=0;j<mine->getcolumn();j++)
                {
                    if(mine->view[i][j]==-1&&mine->gamedata[i][j]!=88)
                        mine->gamedata[i][j]=-777;
                }
        }
        else
            dfs(x,y);
        repaint();
    }
    else if(event->button()==Qt::LeftButton&&mine->view[x][y]!=777&&mine->view[x][y]!=-1)
    {
        int aim=mine->view[x][y];
        int temp_flag=0;
        int error=0;
        for(int dx=x-1;dx<=x+1;dx++)
            for(int dy=y-1;dy<=y+1;dy++)
                if(dx >= 0 && dx< mine->getrow() && dy >= 0&& dy < mine->getcolumn())
                {
                    if(mine->view[dx][dy]==-1&&mine->gamedata[dx][dy]!=88)
                        error=1;
                    if(mine->view[dx][dy]==-1)
                    {
                        temp_flag++;
                    }
                }
        if(temp_flag==aim)
        {
            if(error==1)
            {
                gameover=true;
                runtime->stop();
                gamestart=1;
                alreadyflag=0;
                for(int i=0;i<mine->getrow();i++)
                    for(int j=0;j<mine->getcolumn();j++)
                    {
                        if(mine->view[i][j]==-1&&mine->gamedata[i][j]!=88)
                            mine->gamedata[i][j]=-777;
                    }
                repaint();
                return;
            }
            for(int dx=x-1;dx<=x+1;dx++)
                    for(int dy=y-1;dy<=y+1;dy++)
                        if(dx >= 0 && dx< mine->getrow() && dy >= 0&& dy < mine->getcolumn())
                        {
                            if(mine->view[dx][dy]==777)
                            {
                                dfs(dx,dy);
                                repaint();
                            }
                        }
        }
    }
    else if(event->button()==Qt::RightButton&&(mine->view[x][y]==-1||mine->view[x][y]==777)&&gameover==false)
    {
        mine->view[x][y]=mine->view[x][y]==-1?777:-1;
        if(mine->view[x][y]==-1)
            alreadyflag++;
        else
            alreadyflag--;
        repaint();
    }
    if(whetherwin())
    {
        gameover=true;
        runtime->stop();
        gamestart=1;
        alreadyflag=0;
        QMessageBox message(QMessageBox::NoIcon, " ","成功！");
        message.exec();
    }
}
void MainWindow::dfs(int x,int y)
{
    int flag=0;
    if(mine->view[x][y]!=777)
        return;
    mine->view[x][y]=mine->gamedata[x][y];
    for(int dx=x-1;dx<=x+1;dx++)
        for(int dy=y-1;dy<=y+1;dy++)
        {
            if(dx >= 0 && dx< mine->getrow() && dy >= 0&& dy < mine->getcolumn())
                if(mine->gamedata[dx][dy]==88)
                {
                    flag=1;
                    break;
                }
        }
    if(flag==0)
    {
        for(int dx=x-1;dx<=x+1;dx++)
            for(int dy=y-1;dy<=y+1;dy++)
                if(dx >= 0 && dx< mine->getrow() && dy >= 0&& dy < mine->getcolumn())
                    dfs(dx,dy);
    }
}
void MainWindow::on_secondadd()
{
    mine->addtime();
}
void MainWindow::on_actioneasy_triggered()
{
    mine=new block(9,9,10);
    this->setFixedSize(mine->getwid(),mine->geth());
    runtime->stop();
    alreadyflag=0;
    gameover=false;
    gamestart=1;
    update();
}
void MainWindow::on_actionmeduim_triggered()
{
    mine=new block(16,16,40);
    this->setFixedSize(mine->getwid(),mine->geth());
    runtime->stop();
    alreadyflag=0;
    gameover=false;
    gamestart=1;
    update();
}
void MainWindow::on_actionhard_triggered()
{
    mine=new block(30,16,99);
    this->setFixedSize(mine->getwid(),mine->geth());
    runtime->stop();
    alreadyflag=0;
    gameover=false;
    gamestart=1;
    update();
}
void MainWindow::on_actiondefined_triggered()
{
    runtime->stop();
    alreadyflag=0;
    gameover=false;
    gamestart=1;
    useDefineWindows = new Dialog(this);
    useDefineWindows->show();
}
void MainWindow::on_actionnewgame_triggered()
{
    restart(mine->getrow(),mine->getcolumn(),mine->getboom());
    runtime->stop();
    alreadyflag=0;
    gameover=false;
    gamestart=1;
    update();
}
void MainWindow::on_actionwriter_triggered()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://home.ustc.edu.cn/~lyh_0921/about/")));
}
void MainWindow::on_actionhelp_triggered()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://zhidao.baidu.com/question/1929920644103283427.html")));
}
void begin()
{
    mine=new block(ROW,COLUMN,BOOM_NUM);
    tmp->setFixedSize(mine->getwid(),mine->geth());
    gameover=false;
}
bool whetherwin()
{
    int temp=0;
    for(int i=0;i<mine->getrow();i++)
        for(int j=0;j<mine->getcolumn();j++)
        {
            if(mine->view[i][j]==777||mine->view[i][j]==-1)
                temp++;
        }
    if(temp==mine->getboom())
        return true;
    else
        return false;
}
void restart(int row,int col,int mine_num)
{
    mine=new block(row,col,mine_num);
}

