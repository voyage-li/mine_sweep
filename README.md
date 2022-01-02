## <center>基于Qt实现图形化扫雷</center>

**[摘要]**：扫雷主体部分的c++代码实现，以及Qt的简单介绍，并且通过Qt来实现扫雷游戏的图形化，鼠标点击时间的判断，信号与槽的使用，以及游戏难度的选择以及自定义和记录时间功能的添加。

#### <center>绪论</center>

​	Qt是一个1991年由Qt Company开发的跨平台图形用户界面应用程序开发框架,支持Windows，Linux等不同操作系统，它既可以开发GUI程序，也可用于开发非GUI程序，比如控制台工具和服务器。Qt是面向对象的框架，能够适配大量c++的函数和库，同时可以实现大量单纯c++无法实现的功能。
​	Qt Creator是一个用于Qt开发的轻量级跨平台集成开发环境。Qt Creator可带来两大关键益处：提供首个专为支持跨平台开发而设计的集成开发环境 (`IDE`)，并确保首次接触Qt框架的开发人员能迅速上手和操作。即使不开发Qt应用程序，Qt Creator也是一个简单易用且功能强大的`IDE`。
​	扫雷是最初Windows操作系统为了检测鼠标性能而设计的一款游戏，但是随着Windows系统的不断更新，逐渐完善，收到了广大群众的喜爱，也因此衍生了很多比赛。但是自从Win10开始，系统不再安装扫雷，扫雷游戏也逐渐淡出我们的视野。

#### 一、主体函数的C++实现

##### 	1.游戏的初始化

​	最简单的扫雷游戏是一个9×9的方块，因此，我们可以建立一个9×9的二维数组，先对其进行初始化，然后，在其中存储相关的数据。

```c++
#define ROW 9
#define COL 9
int gamedata[ROW][COL]; //记录原始数据
memset(gamedata, 0, sizeof(gamedata));
```

​	紧接着是不同状态的记录，扫雷游戏每一个小块的状态可以对应表示成的不同的数字。

```c++
//0~8 该方块周围的雷的数量
//88 该方块为雷
//777 该方块处于待点击状态
```

​	其次是雷的生成，简单的扫雷游戏中，会在9×9的81方块中随机生成10个雷，转化成计算机的语言就是，从1\~81中任意取10个数，但是这样的选取有一定的缺点，在我们取出随机数之后，我们很难将随机数与相应的雷产生联系，带来了不必要的麻烦，解决方案是，我们可以生成十组横纵坐标1\~9之间的随机数（避免重复的情况），这样下来，随机数的选取和雷的位置对应能够更加的简单，代码实现如下：

```c++
#define BOOM_NUM 10
int boom_num_now = 0; //已经生成的雷的数量
while (boom_num_now != BOOM_NUM)
{
    //这里随机数使用了QRandomGenerator头文件中的函数
    int x=QRandomGenerator::global()->bounded(0,ROW);   
    int y=QRandomGenerator::global()->bounded(0,COL);
    if (gamedata[x][y] == 88)
        continue;
    else
        gamedata[x][y] = 88;
    boom_num_now++;
}
```

​	再其次是每一个方块周围雷数量的统计，这里我们只需要通过一个循环来计数即可，代码实现如下：

```c++
int tmp;
for (int i = 0; i < ROW; i++)
    for (int j = 0; j < COL; j++)
    {
        tmp = 0;
        if (gamedata[i][j] == 88)
            continue;
        for (int dx = i - 1; dx <= i + 1; dx++)
            for (int dy = j - 1; dy <= j + 1; dy++)
            {
                if (dx >= 0 && dy >= 0 && dx < ROW && dy < COL && gamedata[dx][dy] == 88)
                     tmp++;
             }
         gamedata[i][j] = tmp;
     }
```

​	最后我们要生成一个向玩家展示的数组，来记录每一点击产生的结果，如下所示：

```c++
int view[ROW][COL];
for (int i = 0; i < ROW; i++)
    for (int j = 0; j < COL; j++)
        view[i][j] = 777;
```

##### 2.鼠标点击事件的判断

​	鼠标点击一个方块，即选择了对应左边的数据，如果选中了雷，那么游戏结束，如果选中了其他方块，则需要判断其周围有没有雷，以此来翻开其它的方块，其本质是一个深度搜索(`DFS`)，我们可以通过递归来完成这个过程，具体的思想是：

​	先通过循环判断点击方块一周的方块是否有雷，如果没有雷的话，就相当于我们点击了周围一圈的方块，可以直接递归调用该函数，递归返回的条件分为两种，一种是该方块已经翻开，一种是该方块周围有雷的存在，具体的代码实现如下所示：

```c++
void dfs(int x, int y)
{
    int flag = 0;
    if (view[x][y] != 777)
        return;
    view[x][y] = gamedata[x][y];
    for (int dx = x - 1; dx <= x + 1; dx++)
        for (int dy = y - 1; dy <= y + 1; dy++)
        {
            if (dx >= 0 && dx < ROW && dy >= 0 && dy < COL)
                if (gamedata[dx][dy] == 88)
                {
                    flag = 1;
                    break;
                }
        }
    if (flag == 0)
    {
        for (int dx = x - 1; dx <= x + 1; dx++)
            for (int dy = y - 1; dy <= y + 1; dy++)
                if (dx >= 0 && dx < ROW && dy >= 0 && dy < COL)
                    dfs(dx, dy);
    }
}
```

##### 3.游戏胜利的条件判断

​	扫雷游戏的胜利条件判断较为简单，如果剩余的没有点击的方块数量（没有点击或者已经被标记）和雷数相同，就表示游戏取得了胜利，代码实现如下：

```c++
bool whetherwin()
{
    int temp = 0;
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
        {
            if (view[i][j] == 777)
                temp++;
        }
    if (temp == BOOM_NUM)
        return true;
    else
        return false;
}
```

​	至此，就完成了整个扫雷游戏的主体函数部分，再加上输入输出函数，和一些额外条件的判断，就可以得到一个基本的命令行版本的扫雷游戏。

#### 二、从C++过渡到Qt

##### 1.窗口的搭建

​	打开Qt creator,新建一个Qt Widgets Application，点击mainwindow.ui进入设计界面，通过拖动左栏的窗口控件，完成图形化窗口的搭建。

##### 2.扫雷界面的绘制

​	Qt和绘图相关的主要有两个头文件的内容，分别是`QPixmap`和`QImage`，`QPixmap`主要是针对位图，能够很好的适配不同的屏幕，`QImage`针对的是图像的呈现，扫雷游戏我们更加重要的是图像和屏幕的适配的问题，所以选用`QPixmap`来绘图，首先需要include头文件。

```c++
#include <QPixmap>
#include <QPainter>
```

​	`QPixmap`头文件中主要用来绘图的函数是`drawPixmap()`,根据Qt官方文档的描述，`drawPixmap()`,有多种重载函数，由于为扫雷游戏准备的资源文件已经是确定了像素的，只需要对绘图的位置和不同的图片进行选择，所以选择以下所示的重载函数。

```c++
inline void QPainter::drawPixmap(int x, int y, const QPixmap &pm)// x,y表示需要绘图位置的坐标，pm是需要绘制的图片{    drawPixmap(QPointF(x, y), pm);}
```

​	使用循环，在`paitEvent()`内调用`drawPixmap()`函数即可绘制主要的窗口：

```c++
#define BLOCK_HEIGHT 30
#define BLOCK_WIDTH 20
#define MENU_WIDTH 26+40
QPainter painter(this);for (int i = 0; i < ROW; i++)
{    
    for (int j = 0; j < COL; j++)        
        painter.drawPixmap(i * BLOCK_HEIGHT, MENU_WIDTH + j * BLOCK_WIDTH, view[i][j]);
}
```

##### 3.鼠标点击事件的具体实现

​	根据Qt官方文档，和鼠标点击相关的头文件是`QMouseEvent`，官方文档内，对获取鼠标点击位置的描述函数是：

```c++
inline int x() const { return qRound(l.x()); }
inline int y() const { return qRound(l.y()); }
```

​	这样得到的位置坐标是对应的像素坐标，我们知道每一个方块的边长，通过取余数的方式可以获得具体的在扫雷游戏中的坐标

```c++
int x = event->x() / BLOCK_WIDTH;int y = (event->y() - MENU_WIDTH) / BLOCK_HEIGHT; //需要剪掉菜单栏的距离
```

​	在实际游戏时，鼠标左右键点击的效果不同，`QMouseEvent`中对鼠标点击事件的描述是

```c++
inline Qt::MouseButton button() const { return b; }
```

​	该函数会返回一个枚举类型，对应着不同的鼠标点击，具体的实现如下：

```c++
if (event->button() == Qt::LeftButton) {}
else if (event->button() == Qt::RightButton) {}
```

##### 4.点击数字功能实现

​	在Windows平台的扫雷游戏中，用户可以点击已被翻开的数字方块，如果周围所有的雷已被标记，则可以直接翻开未被标记的方块，如果标记雷的数量是正确的，但是标记的具体方块是错误的，则会直接导致游戏结束，如果已经标记的雷的数量和点击数字方块的数字不同，则直接等待下一次用户的操作。

​	实现该功能的思路是，先判断鼠标左键点击的位置，得到该方块周围雷的数量，然后循环周围已经被标记的雷的数量，以及标记的是否正确，如果标记错误，则可以直接触发游戏结束命令，如果标记正确且和对应的雷数量相同，则调用上文已经叙述过的`dfs()`函数，翻开方块，代码的具体实现如下所示：

```c++
else if (event->button() == Qt::LeftButton && mine->view[x][y] != 777 && mine->view[x][y] != -1)
{    
    int aim = mine->view[x][y];    
    int temp_flag = 0;    
    int error = 0;    
    for (int dx = x - 1; dx <= x + 1; dx++)        
        for (int dy = y - 1; dy <= y + 1; dy++)            
            if (dx >= 0 && dx < mine->getrow() && dy >= 0 && dy < mine->getcolumn())            
            {               
                if (mine->view[dx][dy] == -1 && mine->gamedata[dx][dy] != 88)                    
                    error = 1;                
                if (mine->view[dx][dy] == -1)                
                {                    
                    temp_flag++;
                }            
            }    
    if (temp_flag == aim)    
    {        
        if (error == 1)        
        {            
            gameover = true;            
            runtime->stop();            
            gamestart = 1;            
            alreadyflag = 0;            
            for (int i = 0; i < mine->getrow(); i++)                
                for (int j = 0; j < mine->getcolumn(); j++)                
                {                    
                    if (mine->view[i][j] == -1 && mine->gamedata[i][j] != 88)                        
                        mine->gamedata[i][j] = -777;                
                }            
            repaint();            
            return;        
        }        
        for (int dx = x - 1; dx <= x + 1; dx++)            
            for (int dy = y - 1; dy <= y + 1; dy++)                
                if (dx >= 0 && dx < mine->getrow() && dy >= 0 && dy < mine->getcolumn())                
                {                    
                    if (mine->view[dx][dy] == 777)                    
                    {                        
                        dfs(dx, dy);                        
                        repaint();                    
                    }                
                }    
    }
}
```

##### 5.函数调用结构以及程序的执行步骤

​	用户开始选择开始游戏，程序自动产生两个数组：`gamedata`和`view`，程序自动给`gamedata`进行初始化，`view`的值则全部设置成为UNKNOWN，即尚未打开状态，程序根据数组`view`，将当前的游戏状态通过`drawPixmap()`绘制到窗口上，用户点击窗口，触发`QMouseEvent`，进入函数进行相应的判断，根据鼠标的左右键点击的不同，进入不同的分支，同时每次触发完鼠标点击时间之后，都进行一次是否获胜的判断。同时，定义`bool`类型的全局变量`gameover`，如果游戏已经失败或者已经z取胜，则将`gameover`设置为true，不再进入鼠标点击时间的判断。

#### 三、额外功能的实现

##### 1.不同难度的选择和自定义

- ​	传统扫雷游戏可以选择不同的难度，此次实现的扫雷游戏应该也有这个功能。为了实现这一功能，可以定义一个`block`类，以此来储存不同情况下的横宽以及雷的数量，同时，由于不同的情况下，`gamedata`和`view`的初始化不同，所以游戏的初始化也应该放在`block`类中完成。
    ​	`block`类中主要定义了：扫雷游戏的长，扫雷游戏的高，扫雷游戏雷的数量，当前已经经过的时间。同时上述的成员均为`private`成员，所以同时需要定义`public`的成员函数，来一一对应，获得上述对象的值。

    ​	在整个游戏开始时，先建立一个`block`类的指针，其中第一次进入消息循环时，使用初级难度作为初始化的值、在用户选择不同难度的时侯，可以通过传给指针不同的地址，来进行处理。

    ​	首先类需要处理的是游戏的初始化，由于需要根据类的构造函数来创建数组，所以显然需要动态申请内存空间，这里可以在类中定义二维指针，然后通过`new`来动态开辟内存空间，具体实现如下（这里只展示其中一个数组的初始化方法，另外一个数组的初始化方法完全相同）：

```c++
view = new int *[row];for (int i = 0; i < row; i++)    
    view[i] = new int[column];
for (int i = 0; i < row; i++)    
    for (int j = 0; j < column; j++)    
    {        
        gamedata[i][j] = 0;        
        view[i][j] = 777;    
    }
```

- ​	实现用户自定义游戏难度即是要接收用户输入的数据，可以通过新建一个窗口来接收数据，但在接收数据的途中，需要注意用户输入数据的合理性。行和列数不能为负或者过大，以及用户输入的雷的数量不能多于用户输入的行列数乘积，否则会造成非法访问的问题，导致程序异常退出。

##### 2.剩余雷数量的计算以及呈现

​	定义全局变量`alreadyflag`来记录已经被鼠标左键标记的雷的数量，同时每次检测到鼠标左键点击的时候，根据情况的不同，即时更改，同时，在每轮游戏结束时，将`alreadyflag`变量重新初始化。

​	剩余雷的数量的绘制也应写在`paintEvent()`内部，获得剩余雷的数量之后，使用分支语句，直接将数字呈现给用户。需要注意的是，为了防止用户标记的雷的数量超过游戏本生雷的数量，所以在绘制前需要判断是否剩余未标记雷的数量为负值，代码实现如下：

```c++
int temp_flag = mine->getboom() - alreadyflag;if (temp_flag < 0)//判断剩余的未标记的雷的数量是否为负值
{    painter.drawPixmap((int)((float)(mine->getwid() * 36) / 200) - 30, 5 + MENU_WIDTH - 40, ele_10);    
 temp_flag = -temp_flag;}
else    
    painter.drawPixmap((int)((float)(mine->getwid() * 36) / 200) - 30, 5 + MENU_WIDTH - 40, ele_0);
switch (temp_flag / 10)//绘制十位数字
{
    case 0:	    painter.drawPixmap((int)((float)(mine->getwid() * 36) / 200) - 10, 5 + MENU_WIDTH - 40, ele_0);	    
	break;	
 	case 1:{}	case 2:{}	case 3:{}	case 4:{}	case 5:{}	case 6:{}	case 7:{}	case 8:{}	case 9:{}}switch (temp_flag % 10){}//绘制个位数字
```

##### 3.游戏时间记录与绘制

​	Qt中与时间有关的头文件主要有`QTimer`，新建一个`QTimer`对象，通过调用`start()`函数控制Qt计时器的开始以及时间间隔，通过`connect()`函数，连接`timeout()`信号与自定义的槽函数，随着时间的变化执行相应的不同操作。

​	记录时间变化的槽函数可以使用`block`类的成员函数，在`block`类中初始化一`private`类型的时间变量，每次调用槽函数使该变量递增，即可记录当前时间，具体的代码实现如下：

```c++
//mainwindow.cppblock 
*mine = new block(ROW, COLUMN, BOOM_NUM);runtime = new QTimer(this);connect(runtime, SIGNAL(timeout()), this, SLOT(on_secondadd()));connect(runtime, SIGNAL(timeout()), this, SLOT(update()));
void MainWindow::on_secondadd()
{   
    mine->addtime();
}//block.cppvoid block::addtime(){    time_now++;}//时间绘制部分与雷数量呈现部分相同
```

#### 四、其他功能和细节

##### 1.网址跳转

​	跳转对应网址使用` QDesktopServices`头文件中的`openUrl()`函数：

```c++
QDesktopServices::openUrl(QUrl(QLatin1String("http://home.ustc.edu.cn/")));
```

##### 2.胜利窗口显示

​	需要使用`QMessageBox`头文件，具体实现：

```c++
QMessageBox message(QMessageBox::NoIcon, "title","content");message.exec();
```

#### 五、程序最终效果展示

> 图片找不到了 懒

[扫雷图片素材来源](https://github.com/fengqian-wei/qt-mine-sweeping)

