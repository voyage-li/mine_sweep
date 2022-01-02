#include "block.h"

block::block(int row,int column,int boom)
{
    ROW=row;
    COLUMN=column;
    boom_number=boom;
    WINDOW_WIDTH=row*30;
    WINDOW_HEIGHT=column*30+26+40;
    time_now=0;

    gamedata = new int *[row];
    for(int i = 0;i<row;i++)
        gamedata[i] = new int [column];

    view = new int *[row];
    for(int i = 0;i<row;i++)
        view[i] = new int [column];
    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
        {
            gamedata[i][j]=0;
            view[i][j]=777;
        }
    for(int i=0;i<boom;i++)
    {
        int x=QRandomGenerator::global()->bounded(0,row);
        int y=QRandomGenerator::global()->bounded(0,column);
        if(gamedata[x][y]==88)
        {
            i--;
            continue;
        }
        gamedata[x][y]=88;
    }
    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
        {
            if(gamedata[i][j]==88)
                continue;
            int number=0;
            for(int dx=i-1;dx<=i+1;dx++)
                for(int dy=j-1;dy<=j+1;dy++)
                {
                    if(dx >= 0 && dx< row && dy >= 0&& dy < column)
                        if(gamedata[dx][dy]==88)
                            number++;
                }
            switch(number)
            {
            case 0:gamedata[i][j]=0;break;
            case 1:gamedata[i][j]=1;break;
            case 2:gamedata[i][j]=2;break;
            case 3:gamedata[i][j]=3;break;
            case 4:gamedata[i][j]=4;break;
            case 5:gamedata[i][j]=5;break;
            case 6:gamedata[i][j]=6;break;
            case 7:gamedata[i][j]=7;break;
            case 8:gamedata[i][j]=8;break;
            }
            number=0;
        }

}
block::~block()
{
    for(int i =0;i<ROW;i++)
    {
        delete[]  gamedata[i];
        delete[]  view[i];
    }
    delete [] gamedata;
    delete [] view;
}
int block::getrow()
{
    return ROW;
}
int block::getcolumn()
{
    return COLUMN;
}
int block::getboom()
{
    return boom_number;
}
int block::getwid()
{
    return WINDOW_WIDTH;
}
int block::geth()
{
    return WINDOW_HEIGHT;
}
int block::gettime()
{
    return time_now;
}
void block::addtime()
{
    time_now++;
}
