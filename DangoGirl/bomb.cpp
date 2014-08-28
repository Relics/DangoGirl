#include"bomb.h"
#include"def.h"
/*炸弹的构造函数，传入炸弹生成的坐标和释放者*/
Bomb::Bomb(int x,int y,int master)
{
    this->x=x;
    this->y=y;
    this->master=master;
    lastTime=4000/FRAME;
    next=0;
}

