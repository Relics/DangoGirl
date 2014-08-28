#include"enemy.h"
/*坏人类的构造函数，传入坐标和是否是boss，以及移动的时间？？*/

Enemy::Enemy(int x, int y, int isBoss, int moveTime)
{
    this->x=x;
    this->y=y;
    this->isBoss=isBoss;
    this->moveTime=moveTime;
    this->isAlive=1;
}

