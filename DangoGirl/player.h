#ifndef PLAYER_H
#define PLAYER_H

/*玩家类定义*/
class Player                            //游戏角色
{
public:
    Player(int x,int y);                //坐标
    int x,y;                            //坐标
    int restLife;                       //剩余生命
    int direction;                      //方向 0:不动 1:左 2:下 3:右 4:上
    int defDir;                         //默认图片显示
    int moveSpeed;                      //移动速度
    int atackRange;                     //攻击范围
    int bombCountLimit;                 //炸弹数量限制
    int bombCount;                      //已放炸弹计数
};

#endif // PLAYER_H
