#ifndef ENEMY_H
#define ENEMY_H
/*敌人类类定义*/
class Enemy{
public:
    Enemy(int x,int y,int isBoss,int moveTime);  //构造函数类
    int x;
    int y;
    int isBoss;             //boss不死
    int moveTime;           //移动速度
    int isAlive;            //是否存活
};

#endif // ENEMY_H
