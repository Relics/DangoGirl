#include"item.h"

/*道具的够在函数*/
Item::Item(int id,int x,int y)
{
    this->id=id;
    this->master=-1;                //默认无主人
    this->x=x;
    this->y=y;
    lastTime=-1;                    //接触后才开始计时
}
Item::Item(int id, int lastTime)
{
    this->id=id;
    this->master=2;                 //第一次延时用
    this->lastTime=lastTime;
}

