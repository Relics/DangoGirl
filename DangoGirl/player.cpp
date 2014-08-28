#include"player.h"
#include"def.h"
/*玩家类构造函数，传入坐标*/
Player::Player(int x,int y)
{
    this->x=x;
    this->y=y;
    restLife=100;
    direction=0;
    defDir=1;
    moveSpeed=20/FRAME;
    atackRange=2;
    bombCountLimit=3;
    bombCount=0;
}
