#ifndef BLOCK_H
#define BLOCK_H

#include<QRandomGenerator>

class block
{
public:
    block(int row,int column,int boom);
    ~block();
    int getrow();
    int getcolumn();
    int getboom();
    int getwid();
    int geth();
    int gettime();
    void addtime();
    int **gamedata;
    int **view;
private:
    int ROW;
    int COLUMN;
    int boom_number;
    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;
    int time_now;
};

#endif // BLOCK_H
