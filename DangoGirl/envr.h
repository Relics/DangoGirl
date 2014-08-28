#ifndef ENVR_H
#define ENVR_H

#include <QString>
#include"def.h"

extern int stone[STONESIZE][2];//固定的石头数组定义
extern int stone1[STONESIZE][2];
extern int stone2[STONESIZE][2];
extern int stone3[STONESIZE][2];
/*植物类类定义*/
class Plant{
public:
    Plant(int x,int y);//构造函数
    int x;
    int y;
};

#endif // ENVR_H
