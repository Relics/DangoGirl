#ifndef BOMBMAN_H
#define BOMBMAN_H


#include"bomb.h"
#include"player.h"
#include"item.h"
#include"def.h"
#include"envr.h"
#include"enemy.h"
#include<QWidget>
#include<QMediaPlayer>
/*标签类*/
class QLabel;
/*显示数字类*/
class QLCDNumber;
/*按钮类*/
class QPushButton;
/*定义器类*/
class QTimer;
/*声音类*/
class QSound;
/*游戏类类定义*/
class BombMan:public QWidget
{
    Q_OBJECT
public:
    BombMan(QWidget *parent=0);
    void initGame();                   //游戏设置初始化
    void initWidget(void);             //控件初始化
    void initconnect(void);            //连接初始化
    void layBomb(int master);          //放置炸弹
    void gameOver(int res);            //游戏结束
    void playerMove(void);             //玩家移动
    void bombAbout(void);              //炸弹相关
    void itemAbout();                  //道具相关
    void enemyAbout();                 //敌人相关
    void judgement(void);              //所有判定
    void enemyMove(Enemy * enemy);     //敌人移动
    void gameStart(void);               //游戏开始
    void setmode(int);
    void setplayer1(int);
    void setplayer2(int);
    int mode;//模式
    int player1;//玩家1
    int player2;//玩家2
signals:
private slots:
    void process(void);                 //处理函数

private:
    QLabel *lifeLabel1,*lifeLabel2;     //显示“XX剩余生命值为：”
    QLCDNumber *lifeNum1,*lifeNum2;     //具体现实生命值
    QLabel *mainView;                   //游戏显示窗口
    //QPushButton *startButton;           //开始按键
    QTimer *timer;                      //定时器刷屏

    QMediaPlayer mdLay;
    QMediaPlayer mdBomb;
    QMediaPlayer adLay;
    QMediaPlayer adBomb;
    QMediaPlayer music2;

    //Phonon::MediaObject *mdLay;         //设雷声音
    //Phonon::MediaObject *mdBomb;        //爆炸声音
    //Phonon::AudioOutput *adLay;
    //Phonon::AudioOutput *adBomb;
    //Phonon::MediaObject *music2;

    Player *player[2];
    Bomb   *head;                        //遍历炸弹链表首
    Item   *item;                        //道具
    Plant  *plant[PLANTSIZE];            //仙人掌
    Enemy  *normalEnemy[MAXENEMY];      //敌人
    Enemy  *boss[MAXBOSS];              //boss


    int sthExist[XSIZE][YSIZE];
    //特定坐标所在物 0:空 1:道具 2:爆炸的炸弹 3:仙人掌 4:敌人 5:玩家 6:炸弹 7:石头
    int enemySize;      //
    int bossSize;
protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
};

#endif // BOMBMAN_H
