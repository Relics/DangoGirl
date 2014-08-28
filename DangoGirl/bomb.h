#ifndef BOMB_H
#define BOMB_H

/*炸弹类类定义*/
class Bomb
{
public:
    Bomb(int x,int y,int master);       //炸弹构造函数
    int x,y;                            //炸弹的坐标
    int master;                         //所有者 0:player0  1:player1  2:head
    int lastTime;                       //爆炸剩余时间
    Bomb *next;                         //遍历链表
};

#endif // BOMB_H
