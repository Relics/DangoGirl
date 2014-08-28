#include"bombman.h"
#include"def.h"
#include<QWidget>
#include<QLabel>
#include<QLCDNumber>
#include<QPushButton>
#include<QTimer>
#include<QKeyEvent>
#include<QMessageBox>
#include<QPainter>
#include<QRect>
#include<QImage>
#include<QString>
#include<QBrush>
#include<QPen>
#include<QtCore>
#include<QTime>
#include<QSound>

#include "preFace.h"

BombMan::BombMan(QWidget *parent)
    :QWidget(parent)
    //QWidget 是Qt中所有widget部件(比如QDialog、QPushButton、QLabel)的基类
    //详细见http://blog.csdn.net/dbzhang800/article/details/6737540
{
    setFocusPolicy(Qt::StrongFocus);    //同时响应tab与键盘事件
    setFixedSize(966,526);              //设置窗体大小为(w,h)
    //initGame();/*游戏初始化，主要实现对sthExist数组的初始化*/
    //initWidget();/*控件的初始化*/
    //initconnect();/*初始化连接函数*/

}

void BombMan::setmode(int m)
{
    int i;

    mode = m;
    if( m==1 )
    {
        bossSize=0;
        enemySize = 0;
        for (i = 0;i < STONESIZE;i++)
        {
            stone[i][0] = stone1[i][0];
            stone[i][1] = stone1[i][1];
        }
    }
    else if(m==2)
    {
        bossSize = 1;
        enemySize = 10;
        for (i = 0;i < STONESIZE;i++)
        {
            stone[i][0] = stone2[i][0];
            stone[i][1] = stone2[i][1];
        }
    }
    else if (m==3)
    {
        bossSize = 2;
        enemySize = 20;
        for (i = 0;i < STONESIZE;i++)
        {
            stone[i][0] = stone3[i][0];
            stone[i][1] = stone3[i][1];
        }
    }
    else
    {
        bossSize = 0;
        enemySize = 5;
        for (i = 0;i < STONESIZE;i++)
        {
            stone[i][0] = stone1[i][0];
            stone[i][1] = stone1[i][1];
        }
    }
    initGame();
    initWidget();
    initconnect();
}
void BombMan::setplayer1(int p)
{
    player1 = p;
    if (p == 1) //古河猪
    {
        player[0]->restLife = 50;
        player[0]->atackRange = 2;
        player[0]->bombCountLimit = 5;
    }
    if (p == 2) //小汐
    {
        player[0]->restLife = 100;
        player[0]->atackRange = 2;
        player[0]->bombCountLimit = 4;
    }
    if (p == 3) //坂上智代
    {
        player[0]->restLife = 200;
        player[0]->atackRange = 3;
        player[0]->bombCountLimit = 2;
    }
    if (p == 4) //藤林椋liang
    {
        player[0]->restLife = 150;
        player[0]->atackRange = 2;
        player[0]->bombCountLimit = 3;
    }
}
void BombMan::setplayer2(int p)
{
    player2 = p;
    if (p == 1)
    {
        player[1]->restLife = 50;
        player[1]->atackRange = 2;
        player[1]->bombCountLimit = 4;
    }
    if (p == 2)
    {
        player[1]->restLife = 100;
        player[1]->atackRange = 2;
        player[1]->bombCountLimit = 3;
    }
    if (p == 3)
    {
        player[1]->restLife = 150;
        player[1]->atackRange = 2;
        player[1]->bombCountLimit = 2;
    }
    if (p == 4)
    {
        player[1]->restLife = 200;
        player[1]->atackRange = 2;
        player[1]->bombCountLimit = 1;
    }
}
/*游戏初始化，主要实现对sthExist数组的初始化*/
void BombMan::initGame()
{
    int i,j;
    qsrand(QTime::currentTime().msec());//取时间作为随机数的种子
    for(i=0;i<450/BLOCK;i++)
    {
        for(j=0;j<450/BLOCK;j++)
        {
            sthExist[i][j]=0;//0代表什么都没有
        }
    }
    player[0]=new Player(0,0);
    sthExist[0][0]=5;
    player[1]=new Player(14,14);
    sthExist[14][14]=5;
    head=new Bomb(0,0,2);
    item=new Item(-1,3000/FRAME);                   //伪道具
    for(i=0;i<STONESIZE;i++)                        //摆放岩石
    {
        sthExist[stone[i][0]][stone[i][1]]=7;
    }
    for(i=0;i<PLANTSIZE;i++)                        //摆放仙人掌
    {
        int x,y;
        do
        {
            x=qrand()%15;
            y=qrand()%15;
        }
        while(sthExist[x][y]!=0);
        plant[i]=new Plant(x,y);
        sthExist[x][y]=3;
    }
    for(i=0;i<enemySize;i++)
    {
        int x,y;
        do
        {
            x=qrand()%15;
            y=qrand()%15;
        }
        while(sthExist[x][y]!=0);
        normalEnemy[i]=new Enemy(x,y,0,500/FRAME);
        sthExist[x][y]=4;
    }
    for(i=0;i<bossSize;i++)
    {
        int x,y;
        do
        {
            x=qrand()%15;
            y=qrand()%15;
        }
        while(sthExist[x][y]!=0);
        boss[i]=new Enemy(x,y,1,400/FRAME);
        sthExist[x][y]=4;
    }
}
/*控件的初始化*/
void BombMan::initWidget(void)
{
    /*生命条和生命值的定义*/
    lifeLabel1=new QLabel(this);
    lifeLabel1->setText("1P HP:");
    lifeLabel1->setGeometry(240,5,50,30);//1P HP
    //setGeometry函数设置widget（备注：关于QT widget见http://mobile.51cto.com/widget-290038.htm）的位置及widget所占大小
    //例如：这里的setGeometry指的——是从屏幕上（10，5）(x,y）位置开始（即为最左上角的点），显示一个50*30的界面（宽50，高25）(w,h)

    lifeNum1=new QLCDNumber(this);
    lifeNum1->setSegmentStyle(QLCDNumber::Flat);
    lifeNum1->setGeometry(305,5,120,30);

    lifeLabel2=new QLabel(this);
    lifeLabel2->setText("2P HP:");
    lifeLabel2->setGeometry(525,5,50,30);

    lifeNum2=new QLCDNumber(this);
    lifeNum1->setSegmentStyle(QLCDNumber::Flat);
    lifeNum2->setGeometry(580,5,120,30);

    /*游戏主界面*/
    mainView=new QLabel(this);
    mainView->setGeometry(250,40,450,450);
    mainView->setLineWidth(2);
    mainView->setFrameStyle(QFrame::Box |QFrame::Raised);

    /*定时器*/
    timer=new QTimer;
    timer->stop();
    /*音乐播放的定义*/
    //mdLay=new QMediaPlayer;
    //mdBomb=new QMediaPlayer;
    mdLay.setMedia(QUrl::fromLocalFile("./music/lay.wav"));
    mdBomb.setMedia(QUrl::fromLocalFile("./music/bomb.wav"));

    //mdLay=new Phonon::MediaObject;
    //mdBomb=new Phonon::MediaObject;
    //mdLay->setCurrentSource(Phonon::MediaSource("./sound/lay.wav"));
    //mdBomb->setCurrentSource(Phonon::MediaSource("./sound/bomb.WAV"));

    //adLay=new Phonon::AudioOutput;
    //adBomb=new Phonon::AudioOutput;
    //Phonon::createPath(mdLay,adLay);
    //Phonon::createPath(mdBomb,adBomb);
}

/*初始化连接函数
*1.连接了timeout()信号和process()处理函数
*2连接了clicked()信号和clicked()处理函数
*/
void BombMan::initconnect(void)
{
    connect(timer,SIGNAL(timeout()),this,SLOT(process()));
}
/*游戏开始函数，显示生命条和启动刷新定时器*/
void BombMan::gameStart(void)
{
    lifeNum1->display(player[0]->restLife);
    lifeNum2->display(player[1]->restLife);
    if(!timer->isActive())
        timer->start(FRAME);
    update();
    music2.setMedia(QUrl::fromLocalFile("./music/snap.wma"));
    //music2= Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource("./music/snap.wma"));
    music2.play();
}
/*定时器一到会处理的函数*/
void BombMan::process(void)
{
    playerMove();//玩家的移动
    bombAbout();//炸弹的相关处理
    itemAbout();//道具相关处理
    enemyAbout();//坏人相关处理
    judgement();//一些判断
    update();//再次刷新
}
/*对玩家按键的处理*/
void BombMan::keyPressEvent(QKeyEvent * event)
{
    if(timer->isActive())
    {
        switch(event->key())
        {
            case Qt::Key_W:
                            player[0]->direction=4;
                            break;
            case Qt::Key_D:
                            player[0]->direction=3;
                            break;
            case Qt::Key_S:
                            player[0]->direction=2;
                            break;
            case Qt::Key_A:
                            player[0]->direction=1;
                            break;
            case Qt::Key_Space:
                            layBomb(0);//玩家1放的炸弹
                            break;
            case Qt::Key_Up:
                            player[1]->direction=4;
                            break;
            case Qt::Key_Right:
                            player[1]->direction=3;
                            break;
            case Qt::Key_Down:
                            player[1]->direction=2;
                            break;
            case Qt::Key_Left:
                            player[1]->direction=1;
                            break;
            case Qt::Key_Control:
                            layBomb(1);//玩家2放的炸弹
                            break;
            default:
                            player[0]->direction=player[0]->direction;
                            player[1]->direction=player[1]->direction;
        }
    }
}
/*放炸弹的函数*/
void BombMan::layBomb(int master)
{
        if((player[master]->bombCount) < (player[master]->bombCountLimit))
        {
            mdLay.play();//放炸弹的音乐
            Bomb *p=head;//加入到炸弹链表
            while(p->next!=0)
            {
                p=p->next;
            }
            p->next=new Bomb(player[master]->x,player[master]->y,master);
            player[master]->bombCount=player[master]->bombCount+1;
            sthExist[player[master]->x][player[master]->y]=6;
        }
}

/*游戏结束的函数，要么玩家1赢，要么玩家2赢*/
void BombMan::gameOver(int res)
{
    int m;
    int p1,p2;
    //QMessageBox::about(0,"info",QString::number(sthExist[player[0]->x][player[0]->y]));
    //QMessageBox::about(0,"info",QString::number(sthExist[player[1]->x][player[1]->y]));
    music2.stop();
    if(res==0)
    {
        QMessageBox::about(this,"Resault","player1 win the game!");

    }
    else
    {
        QMessageBox::about(this,"Resault","Player2 win the game!");
    }
    m = mode;
    p1 = player1;
    p2 = player2;
    preFace *face=new preFace;
    face->bombMan.setmode(m);
    face->bombMan.setplayer1(p1);
    face->bombMan.setplayer2(p2);
    face->gameEnd();
    //关闭定时器
    timer->stop();
    //释放玩家和炸弹以及植物和boss
    free(player[0]);
    free(player[1]);
    Bomb *p=head;
    while(p)
    {
        p=p->next;
        free(head);
        head=p;
    }
    for(int i=0;i<PLANTSIZE;i++)
    {
        free(plant[i]);
    }
    for(int i=0;i<enemySize;i++)
    {
        free(normalEnemy[i]);
    }
    for(int i=0;i<bossSize;i++)
    {
        free(boss[i]);
    }
    //再一次调用初始化游戏，新一轮的游戏
    initGame();
    close();

}
/*此函数是在调用 update()，repaint()的时候，paintEvent()会被调用
*另外，当界面有任何改变的时候，paintEvent()也会被调用
*这种界面的改变包括界面从隐藏到显示，界面尺寸改变，当然还包括界面内容改变的时候会被调用
*/
void BombMan::paintEvent(QPaintEvent *)
{
    QPainter painter(this);                   //铺白
    QRect rect=QRect(10,40,450,450);
    painter.fillRect(rect,Qt::white);
    QImage mapImg;
    mapImg.load("./images/bg3.jpg");
    painter.drawImage(10,40,mapImg);

    QImage itemImg;                           //道具
    QString itmImgStr[3]={"./images/i001.gif","./images/i002.gif","./images/i003.gif"};
    if(item->id >= 0)
    {
        if(sthExist[item->x][item->y]==1)
        {
            itemImg.load(itmImgStr[item->id]);
            painter.drawImage(250+BLOCK*(item->x),40+BLOCK*(item->y),itemImg);
        }
    }
    QImage stoneImg[4];                                                             //石头 为4张图片
    QString stoneStr[4]={"./images/stone1.jpg","./images/stone2.jpg","./images/stone3.jpg","./images/stone4.jpg"};
    for(int i=0;i<4;i++)
    {
        stoneImg[i].load(stoneStr[i]);
    }
    for(int i=0;i<STONESIZE;i++)
    {
        painter.drawImage(250+BLOCK*stone[i][0],40+BLOCK*stone[i][1],stoneImg[i % 4]);
    }

    QImage enemyImg,bossImg;                                                        //敌人，包括普通和boss
    QString enemyStr="./images/enemy2.gif";
    QString bossStr="./images/enemy1.gif";
    enemyImg.load(enemyStr);
    bossImg.load(bossStr);
    for(int i=0;i<enemySize;i++)
    {
        if(sthExist[normalEnemy[i]->x][normalEnemy[i]->y]==4&&((normalEnemy[i]->x)<15)&&((normalEnemy[i]->x)>=0)&&((normalEnemy[i]->y)<15)&&((normalEnemy[i]->y)>=0))
        {
            if (mode != 4)
            {
                painter.drawImage(250+BLOCK*(normalEnemy[i]->x),40+BLOCK*(normalEnemy[i]->y),enemyImg);
            }
        }
    }
    for(int i=0;i<bossSize;i++)
    {
        if(sthExist[boss[i]->x][boss[i]->y]==4&&((boss[i]->x)<15)&&((boss[i]->x)>=0)&&((boss[i]->y)<15)&&((boss[i]->y)>=0))
        {
            painter.drawImage(250+BLOCK*(boss[i]->x),40+BLOCK*(boss[i]->y),bossImg);
        }
    }

    QImage plantImg;                                                              //仙人掌
    QString plantStr="./images/plant.gif";
    plantImg.load(plantStr);
    for(int i=0;i<PLANTSIZE;i++)
    {
        if(sthExist[plant[i]->x][plant[i]->y]==3)
        {
            painter.drawImage(250+BLOCK*(plant[i]->x),40+BLOCK*(plant[i]->y),plantImg);
        }
    }
                                              //载人
    QImage image[2];
    QString imgStr[2][4];
    switch (player1)
    {
    case 1:imgStr[0][0] = "./images/p0.gif";
           imgStr[0][1] = "./images/p0.gif";
           imgStr[0][2] = "./images/p0.gif";
           imgStr[0][3] = "./images/p0.gif";
           break;
    case 2:imgStr[0][0] = "./images/p1.gif";
           imgStr[0][1] = "./images/p1.gif";
           imgStr[0][2] = "./images/p1.gif";
           imgStr[0][3] = "./images/p1.gif";
           break;
    case 3:imgStr[0][0] = "./images/p2.gif";
           imgStr[0][1] = "./images/p2.gif";
           imgStr[0][2] = "./images/p2.gif";
           imgStr[0][3] = "./images/p2.gif";
           break;
    case 4:imgStr[0][0] = "./images/p3.gif";
           imgStr[0][1] = "./images/p3.gif";
           imgStr[0][2] = "./images/p3.gif";
           imgStr[0][3] = "./images/p3.gif";
           break;
    }
    switch (player2)
    {
    case 1:imgStr[1][0] = "./images/p0.gif";
           imgStr[1][1] = "./images/p0.gif";
           imgStr[1][2] = "./images/p0.gif";
           imgStr[1][3] = "./images/p0.gif";
           break;
    case 2:imgStr[1][0] = "./images/p1.gif";
           imgStr[1][1] = "./images/p1.gif";
           imgStr[1][2] = "./images/p1.gif";
           imgStr[1][3] = "./images/p1.gif";
           break;
    case 3:imgStr[1][0] = "./images/p2.gif";
           imgStr[1][1] = "./images/p2.gif";
           imgStr[1][2] = "./images/p2.gif";
           imgStr[1][3] = "./images/p2.gif";
           break;
    case 4:imgStr[1][0] = "./images/p3.gif";
           imgStr[1][1] = "./images/p3.gif";
           imgStr[1][2] = "./images/p3.gif";
           imgStr[1][3] = "./images/p3.gif";
           break;
    }
    //QString imgStr[2][4]={{"./images/p02.gif","./images/p01.gif","./images/p03.gif","./images/p04.gif"},
    //                      {"./images/p12.gif","./images/p11.gif","./images/p13.gif","./images/p14.gif"}};//左正右上
    //static int def[2]={1,1};
    int x[2];
    int y[2];
    x[0]=250+BLOCK*(player[0]->x);
    y[0]=40+BLOCK*(player[0]->y);
    x[1]=250+BLOCK*(player[1]->x);
    y[1]=40+BLOCK*(player[1]->y);
    for(int i=0;i<2;i++)
    {
        if(player[i]->direction > 0)
        {
            player[i]->defDir=player[i]->direction-1;  //方向 0:不动 1:左 2:下 3:右 4:上，，默认为1
            image[i].load(imgStr[i][player[i]->defDir]);
            painter.drawImage(x[i],y[i],image[i]);
            player[i]->direction=0;
        }
        else
        {
            image[i].load(imgStr[i][player[i]->defDir]);
            painter.drawImage(x[i],y[i],image[i]);
        }
    }

    //painter.drawImage(x0,y0,image1);
    //painter.drawImage(x1,y1,image2);

    Bomb *p=head->next;                              //炸弹
    //QBrush brush;
    //QPen pen;
    QImage BombImg1;                                                              //仙人掌
    QString BombStr1="./images/b2.png";
    BombImg1.load(BombStr1);
    QImage BombImg2;                                                              //仙人掌
    QString BombStr2="./images/b1.png";
    BombImg2.load(BombStr2);
    QImage BombImg3;                                                              //仙人掌
    QString BombStr3="./images/b4.png";
    BombImg3.load(BombStr3);
    QImage BombImg4;                                                              //仙人掌
    QString BombStr4="./images/b3.png";
    BombImg4.load(BombStr4);
    while(p)
    {
        int t=((p->lastTime)*FRAME)/100;         //化为以0.1秒为单位，frame是毫秒
        if( t > 10 )
        {
            painter.setBrush(Qt::black);
            painter.setPen(Qt::black);
            if((t%28)<7)
            {
                //painter.drawEllipse((p->x)*BLOCK+10,((p->y)*BLOCK+40),BLOCK,BLOCK);
                painter.drawImage((p->x)*BLOCK+250,(p->y)*BLOCK+40,BombImg1);
            }
            else if ((t%28)<14)
            {
                //painter.drawEllipse((p->x)*BLOCK+10,((p->y)*BLOCK+40),BLOCK*2/3,BLOCK*2/3);
                painter.drawImage((p->x)*BLOCK+250,(p->y)*BLOCK+40,BombImg2);
            }
            else if ((t%28)<21)
            {
                painter.drawImage((p->x)*BLOCK+250,(p->y)*BLOCK+40,BombImg3);
            }
            else
            {
                painter.drawImage((p->x)*BLOCK+250,(p->y)*BLOCK+40,BombImg4);
            }
        }
        else
        {
            painter.setBrush(Qt::red);
            painter.setPen(Qt::red);
            if(t>8)//炸掉上下左右共4个格子
            {
                painter.drawRect((p->x)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->x > 0)&&(sthExist[p->x-1][p->y]<7))
                    painter.drawRect(((p->x)-1)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->x < 14)&&(sthExist[(p->x)+1][p->y]<7))
                    painter.drawRect(((p->x)+1)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->y > 0)&&(sthExist[p->x][p->y-1]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)-1)*BLOCK+40),BLOCK,BLOCK);
                if((p->y < 14)&&(sthExist[p->x][p->y+1]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)+1)*BLOCK+40),BLOCK,BLOCK);
            }
            else if(t>7)//炸掉上下左右共8个格子
            {
                painter.drawRect((p->x)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->x > 0)&&(sthExist[p->x-1][p->y]<7))
                    painter.drawRect(((p->x)-1)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->x < 14)&&(sthExist[(p->x)+1][p->y]<7))
                    painter.drawRect(((p->x)+1)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->y > 0)&&(sthExist[p->x][p->y-1]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)-1)*BLOCK+40),BLOCK,BLOCK);
                if((p->y < 14)&&(sthExist[p->x][p->y+1]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)+1)*BLOCK+40),BLOCK,BLOCK);
                if((p->x > 1)&&(sthExist[p->x-2][p->y]<7))
                    painter.drawRect(((p->x)-2)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->x < 13)&&(sthExist[(p->x)+2][p->y]<7))
                    painter.drawRect(((p->x)+2)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->y > 1)&&(sthExist[p->x][p->y-2]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)-2)*BLOCK+40),BLOCK,BLOCK);
                if((p->y < 13)&&(sthExist[p->x][p->y+2]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)+2)*BLOCK+40),BLOCK,BLOCK);
            }
            else if((player[p->master]->atackRange) > 2)//攻击范围超过2，炸掉共12个格子
            {
                painter.drawRect((p->x)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->x > 0)&&(sthExist[p->x-1][p->y]<7))
                    painter.drawRect(((p->x)-1)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->x < 14)&&(sthExist[(p->x)+1][p->y]<7))
                    painter.drawRect(((p->x)+1)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->y > 0)&&(sthExist[p->x][p->y-1]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)-1)*BLOCK+40),BLOCK,BLOCK);
                if((p->y < 14)&&(sthExist[p->x][p->y+1]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)+1)*BLOCK+40),BLOCK,BLOCK);
                if((p->x > 1)&&(sthExist[p->x-2][p->y]<7))
                    painter.drawRect(((p->x)-2)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->x < 13)&&(sthExist[(p->x)+2][p->y]<7))
                    painter.drawRect(((p->x)+2)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->y > 1)&&(sthExist[p->x][p->y-2]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)-2)*BLOCK+40),BLOCK,BLOCK);
                if((p->y < 13)&&(sthExist[p->x][p->y+2]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)+2)*BLOCK+40),BLOCK,BLOCK);
                if((p->x > 2)&&(sthExist[p->x-3][p->y]<7))
                    painter.drawRect(((p->x)-3)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->x < 12)&&(sthExist[(p->x)+3][p->y]<7))
                    painter.drawRect(((p->x)+3)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->y > 2)&&(sthExist[p->x][p->y-3]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)-3)*BLOCK+40),BLOCK,BLOCK);
                if((p->y < 12)&&(sthExist[p->x][p->y+3]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)+3)*BLOCK+40),BLOCK,BLOCK);
            }
            else//否则炸掉8个格子
            {
                painter.drawRect((p->x)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->x > 0)&&(sthExist[p->x-1][p->y]<7))
                    painter.drawRect(((p->x)-1)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->x < 14)&&(sthExist[(p->x)+1][p->y]<7))
                    painter.drawRect(((p->x)+1)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->y > 0)&&(sthExist[p->x][p->y-1]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)-1)*BLOCK+40),BLOCK,BLOCK);
                if((p->y < 14)&&sthExist[p->x][p->y+1]<7)
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)+1)*BLOCK+40),BLOCK,BLOCK);
                if((p->x > 1)&&(sthExist[p->x-2][p->y]<7))
                    painter.drawRect(((p->x)-2)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->x < 13)&&(sthExist[(p->x)+2][p->y]<7))
                    painter.drawRect(((p->x)+2)*BLOCK+250,((p->y)*BLOCK+40),BLOCK,BLOCK);
                if((p->y > 1)&&(sthExist[p->x][p->y-2]<7))
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)-2)*BLOCK+40),BLOCK,BLOCK);
                if((p->y < 13)&&sthExist[p->x][p->y+2]<7)
                    painter.drawRect((p->x)*BLOCK+250,(((p->y)+2)*BLOCK+40),BLOCK,BLOCK);
            }
        }
        p=p->next;
    }

}
/*玩家移动函数*/
void BombMan::playerMove(void)
{
    for(int i=0;i<2;i++)
    {
        switch(player[i]->direction)
        {
            case 1:
                if(player[i]->x > 0)
                {
                    if(sthExist[(player[i]->x)-1][player[i]->y]<5)
                    {
                        if(sthExist[(player[i]->x)-1][player[i]->y]==0)
                        {
                            sthExist[(player[i]->x)-1][player[i]->y]=5;
                        }
                        if(sthExist[player[i]->x][player[i]->y]==5)
                        {
                            sthExist[player[i]->x][player[i]->y]=0;
                        }
                        player[i]->x=player[i]->x-1;
                    }
                }
                break;
            case 2:
                if(player[i]->y < 14)
                {
                    //QMessageBox::information(0,"0",QString::number(sthExist[player[0]->x+1][player[0]->y+1]),10);
                    if(sthExist[player[i]->x][(player[i]->y)+1]<5)
                    {
                        if(sthExist[player[i]->x][player[i]->y+1]==0)
                        {
                            sthExist[player[i]->x][player[i]->y+1]=5;
                        }
                        if(sthExist[player[i]->x][player[i]->y]==5)
                        {
                            sthExist[player[i]->x][player[i]->y]=0;
                        }
                        player[i]->y=player[i]->y+1;
                    }
                }
                break;
            case 3:
                if(player[i]->x < 14)
                {
                    if(sthExist[(player[i]->x)+1][player[i]->y]<5)
                    {
                        if(sthExist[(player[i]->x)+1][player[i]->y]==0)
                        {
                            sthExist[(player[i]->x)+1][player[i]->y]=5;
                        }
                        if(sthExist[player[i]->x][player[i]->y]==5)
                        {
                            sthExist[player[i]->x][player[i]->y]=0;
                        }
                        player[i]->x=player[i]->x+1;
                    }
                }
                break;
            case 4:
                if(player[i]->y > 0)
                {
                    if(sthExist[player[i]->x][(player[i]->y)-1]<5)
                    {
                        if(sthExist[player[i]->x][(player[i]->y)-1]==0)
                        {
                            sthExist[player[i]->x][(player[i]->y)-1]=5;
                        }
                        if(sthExist[player[i]->x][player[i]->y]==5)
                        {
                            sthExist[player[i]->x][player[i]->y]=0;
                        }
                        player[i]->y=player[i]->y-1;
                    }
                }
                break;
            default:
                if((sthExist[player[i]->x][player[i]->y]==0))
                {
                    sthExist[player[i]->x][player[i]->y]=5;
                }
                player[i]->direction=0;
                break;
        }
        //player[i]->direction=0;
    }
}
/*炸弹相关函数
*用一个链表串起炸弹，用FIFO的方式爆炸炸弹
*/
void BombMan::bombAbout(void)
{
    Bomb *p=head->next;
    while(p)
    {
        p->lastTime=p->lastTime-1;
        int tmp=p->lastTime;
        if(tmp < (1000/FRAME))
        {
            mdBomb.play();
            sthExist[p->x][p->y]=2;//爆炸的炸弹
            //之后模拟炸弹爆炸
            if(tmp < (900/FRAME))//给上下左右4个位置放上炸弹的影响
            {
                if(((p->x)>0)&&(sthExist[p->x-1][p->y]<7))
                    sthExist[(p->x)-1][p->y]=2;
                if(((p->x)<14)&&(sthExist[p->x+1][p->y]<7))
                    sthExist[(p->x)+1][p->y]=2;
                if(((p->y)>0)&&(sthExist[p->x][p->y-1]<7))
                    sthExist[p->x][(p->y)-1]=2;
                if(((p->y)<14)&&(sthExist[p->x][p->y+1]<7))
                    sthExist[p->x][(p->y)+1]=2;
                if(tmp < (800/FRAME))//给距离为2 的上下左右4个位置放上炸弹的影响
                {
                    if(((p->x)>1)&&(sthExist[p->x-2][p->y]<7))
                        sthExist[(p->x)-2][p->y]=2;
                    if(((p->x)<13)&&(sthExist[p->x+2][p->y]<7))
                        sthExist[(p->x)+2][p->y]=2;
                    if(((p->y)>1)&&(sthExist[p->x][p->y-2]<7))
                        sthExist[p->x][(p->y)-2]=2;
                    if(((p->y)<13)&&(sthExist[p->x][p->y+2]<7))
                        sthExist[p->x][(p->y)+2]=2;
                    if(((player[p->master]->atackRange) > 2)&&(tmp < (700/FRAME)))//给距离为3的上下左右4个位置放上炸弹的影响
                    {
                        if(((p->x)>2)&&(sthExist[p->x-3][p->y]<7))
                            sthExist[(p->x)-3][p->y]=2;
                        if(((p->x)<12)&&(sthExist[p->x+3][p->y]<7))
                            sthExist[(p->x)+3][p->y]=2;
                        if(((p->y)>2)&&(sthExist[p->x][p->y-3]<7))
                            sthExist[p->x][(p->y)-3]=2;
                        if(((p->y)<12)&&(sthExist[p->x][p->y+3]<7))
                            sthExist[p->x][(p->y)+3]=2;
                    }
                    if(tmp == 0)//清除炸弹的影响
                    {
                        sthExist[p->x][p->y]=0;
                        if(((p->x)>0)&&(sthExist[p->x-1][p->y]<7))
                            sthExist[(p->x)-1][p->y]=0;
                        if(((p->x)<14)&&(sthExist[p->x+1][p->y]<7))
                            sthExist[(p->x)+1][p->y]=0;
                        if(((p->y)>0)&&(sthExist[p->x][p->y-1]<7))
                            sthExist[p->x][(p->y)-1]=0;
                        if(((p->y)<14)&&(sthExist[p->x][p->y+1]<7))
                            sthExist[p->x][(p->y)+1]=0;
                        if(((p->x)>1)&&(sthExist[p->x-2][p->y]<7))
                            sthExist[(p->x)-2][p->y]=0;
                        if(((p->x)<13)&&(sthExist[p->x+2][p->y]<7))
                            sthExist[(p->x)+2][p->y]=0;
                        if(((p->y)>1)&&(sthExist[p->x][p->y-2]<7))
                            sthExist[p->x][(p->y)-2]=0;
                        if(((p->y)<13)&&(sthExist[p->x][p->y+2]<7))
                            sthExist[p->x][(p->y)+2]=0;
                        if((player[p->master]->atackRange) > 2)
                        {
                            if(((p->x)>2)&&(sthExist[p->x-3][p->y]<7))
                                sthExist[(p->x)-3][p->y]=0;
                            if(((p->x)<12)&&(sthExist[p->x+3][p->y]<7))
                                sthExist[(p->x)+3][p->y]=0;
                            if(((p->y)>2)&&(sthExist[p->x][p->y-3]<7))
                                sthExist[p->x][(p->y)-3]=0;
                            if(((p->y)<12)&&(sthExist[p->x][p->y+3]<7))
                                sthExist[p->x][(p->y)+3]=0;
                        }
                        //玩家炸弹数减一
                        player[p->master]->bombCount=(player[p->master]->bombCount)-1;
                        //释放炸弹
                        Bomb *tp=head;
                        while((tp->next)!=p)
                            tp=tp->next;
                        tp->next=p->next;
                        free(p);
                    }
                }
            }
        }
        p=p->next;
    }
}
//道具相关，还是没有明白lasttime的意思
void BombMan::itemAbout()
{
    if(item->master >= 0)                   //激活态
    {
        item->lastTime=item->lastTime-1;
        if(item->lastTime == 0)
        {
        /*    switch(item->id)
            {
            case ID_COUNT:
            case ID_POWER:
            default:
            }
         */
            int x,y;
            free(item);
            do
            {
                x=qrand()%13+1;
                y=qrand()%13+1;
            }
            while(sthExist[x][y]!=0);
            item=new Item(qrand()%3,x,y);            //暂时只使用三个道具，随机用一个道具
            sthExist[x][y]=1;
        }
    }
    else
    {
        if(sthExist[item->x][item->y]==0)
        {
            free(item);
            head=new Bomb(0,0,2);//又生成一个炸弹？
            item=new Item(-1,30000/FRAME);
        }
    }
}
/*坏人相关的函数，如果在炸弹的范围则死，如果在只有玩家和空闲的地方则继续移动*/
void BombMan::enemyAbout()
{
    for(int i=0;i<enemySize;i++)
    {
        if(sthExist[normalEnemy[i]->x][normalEnemy[i]->y]==2)
        {
            normalEnemy[i]->isAlive=0;
        }
        if(normalEnemy[i]->isAlive==1)
        {
            if((sthExist[normalEnemy[i]->x][normalEnemy[i]->y]==0)||
                    (sthExist[normalEnemy[i]->x][normalEnemy[i]->y]==5))
            {
                sthExist[normalEnemy[i]->x][normalEnemy[i]->y]=4;
            }
            enemyMove(normalEnemy[i]);
        }
    }
    for(int i=0;i<bossSize;i++)
    {
        if((sthExist[boss[i]->x][boss[i]->y]==0)||
                (sthExist[boss[i]->x][boss[i]->y]==5))
        {
            sthExist[boss[i]->x][boss[i]->y]=4;
        }
        enemyMove(boss[i]);
    }
}

void BombMan::judgement(void)
{
    //玩家吃道具进行操作，对道具进行判断，并给玩家增强功能
    for(int i=0;i<2;i++)
    {
        if(sthExist[player[i]->x][player[i]->y]==1)
        {
            switch(item->id)
            {
            case ID_COUNT:
                player[i]->bombCountLimit=player[i]->bombCountLimit+1;
                break;
            case ID_POWER:
                player[i]->atackRange=player[i]->atackRange+1;
                break;
            case ID_HEAL:
                player[i]->restLife=player[i]->restLife+20;
                lifeNum1->display(player[0]->restLife);
                lifeNum2->display(player[1]->restLife);
                break;
            default:
                i=i;
            }
            item->lastTime=1500/FRAME;
            item->master=i;
            sthExist[player[i]->x][player[i]->y]=5;
        }
        else if(sthExist[player[i]->x][player[i]->y]==2)//如果玩家走到了爆炸炸弹的范围，则减少生命值并重新表示生命
        {
            player[i]->restLife=(player[i]->restLife)-1;
            lifeNum1->display(player[0]->restLife);
            lifeNum2->display(player[1]->restLife);
            if((player[i]->restLife)<=0)//判断游戏是否结束
            {
                if(i==0)
                    gameOver(1);
                else
                    gameOver(0);
                return;
            }
        }
        else if(sthExist[player[i]->x][player[i]->y]==3)//碰到仙人掌则也减少生命
        {
            player[i]->restLife=(player[i]->restLife)-1;
            lifeNum1->display(player[0]->restLife);
            lifeNum2->display(player[1]->restLife);
            if((player[i]->restLife)<=0)
            {
                if(i==0)
                    gameOver(1);
                else
                    gameOver(0);
                return;
            }
        }
        else if(sthExist[player[i]->x][player[i]->y]==4)//碰到坏人减少生命
        {
            player[i]->restLife=(player[i]->restLife)-1;
            lifeNum1->display(player[0]->restLife);
            lifeNum2->display(player[1]->restLife);
            if((player[i]->restLife)<=0)
            {
                if(i==0)
                    gameOver(1);
                else
                    gameOver(0);
                return;
            }
        }

    }
    Bomb *p=head->next;
    while(p)
    {
        if(sthExist[p->x][p->y]==2)//如果炸弹所处位置在爆炸炸弹范围，则被引爆
        {
            if((p->lastTime)>1000/FRAME)
                p->lastTime=1000/FRAME;
        }
        p=p->next;
    }
}
/*核心算法，AI的移动算法*/
void BombMan::enemyMove(Enemy *enemy)
{
    enemy->moveTime=enemy->moveTime-1;
     /* if(enemy->moveTime<10)
    {
        QMessageBox::about(0,"info",QString::number(enemy->x));
    }*/
    if(enemy->moveTime==0)
    {
        //QMessageBox::about(0,"info","here");
        if(enemy->isBoss)
        {
            enemy->moveTime=300/FRAME;              //重装值，Boss的移动速度为300/Frame，越小越快
        }
        else
        {
            enemy->moveTime=400/FRAME;              //重装值，小怪的移动速度为400/Frame，越小越快
        }
        int x[2],y[2],z[2];
        for(int i=0;i<2;i++)                   //计算与两个玩家的距离
        {
            if((player[i]->x)>(enemy->x))
            {
                x[i]=(player[i]->x)-(enemy->x);
            }
            else
            {
                x[i]=(enemy->x)-(player[i]->x);
            }
            if((player[i]->y)>(enemy->y))
            {
                y[i]=(player[i]->y)-(enemy->y);
            }
            else
            {
                y[i]=(enemy->y)-(player[i]->y);
            }
            z[i]=x[i]*x[i]+y[i]*y[i];
        }

        if(z[0]<z[1])                                   //距离玩家1较近,则向玩家1移动
        {
            if(x[0]>y[0])                               //横坐标更长，横向靠近
            {
                if((player[0]->x)<(enemy->x))           //玩家1在enemy左边
                {
                    if(sthExist[enemy->x-1][enemy->y]<6)//如果enemy左边没石头，炸弹,则向左移动
                    {
                        if((sthExist[enemy->x-1][enemy->y]==0)||(sthExist[enemy->x-1][enemy->y]==5))
                        {
                            sthExist[enemy->x-1][enemy->y]=4;
                        }
                        if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                        {
                            sthExist[enemy->x][enemy->y]=0;
                        }
                        enemy->x=enemy->x-1;
                    }
                    else                               //看看纵向移动
                    {
                        if((player[0]->y)<(enemy->y)) //如果玩家1在enemy上面
                        {
                            if(sthExist[enemy->x][enemy->y-1]<6)//如果enemy上边没石头，炸弹,则向上移动
                            {
                                if((sthExist[enemy->x][enemy->y-1]==0)||(sthExist[enemy->x][enemy->y-1]==5))
                                {
                                    sthExist[enemy->x][enemy->y-1]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->y=enemy->y-1;
                            }
                        }
                        else                           //如果玩家1在enemy下面
                        {
                            if(sthExist[enemy->x][enemy->y+1]<6)//如果enemy下边没石头，炸弹,则向下移动
                            {
                                if((sthExist[enemy->x][enemy->y+1]==0)||(sthExist[enemy->x][enemy->y+1]==5))
                                {
                                    sthExist[enemy->x][enemy->y+1]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->y=enemy->y+1;
                            }
                        }
                    }
                }
                else                                    //玩家1在enemy右边
                {
                    if(sthExist[enemy->x+1][enemy->y]<6)//如果enemy右边没石头，炸弹,则向右移动
                    {
                        if((sthExist[enemy->x+1][enemy->y]==0)||(sthExist[enemy->x+1][enemy->y]==5))
                        {
                            sthExist[enemy->x+1][enemy->y]=4;
                        }
                        if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                        {
                            sthExist[enemy->x][enemy->y]=0;
                        }
                        enemy->x=enemy->x+1;
                    }
                    else                               //看看纵向移动
                    {
                        if((player[0]->y)<(enemy->y)) //如果玩家1在enemy上面
                        {
                            if(sthExist[enemy->x][enemy->y-1]<6)//如果enemy上边没石头，炸弹,则向上移动
                            {
                                if((sthExist[enemy->x][enemy->y-1]==0)||(sthExist[enemy->x][enemy->y-1]==5))
                                {
                                    sthExist[enemy->x][enemy->y-1]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->y=enemy->y-1;
                            }
                        }
                        else                           //如果玩家1在enemy下面
                        {
                            if(sthExist[enemy->x][enemy->y+1]<6)//如果enemy下边没石头，炸弹,则向下移动
                            {
                                if((sthExist[enemy->x][enemy->y+1]==0)||(sthExist[enemy->x][enemy->y+1]==5))
                                {
                                    sthExist[enemy->x][enemy->y+1]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->y=enemy->y+1;
                            }
                        }
                    }
                }
            }
            else                                        //纵坐标更长，纵向靠近
            {
                if((player[0]->y)<(enemy->y))           //玩家1在enemy上边
                {
                    if(sthExist[enemy->x][enemy->y-1]<6)//如果enemy上边没石头，炸弹,则向左移动
                    {
                        if((sthExist[enemy->x][enemy->y-1]==0)||(sthExist[enemy->x][enemy->y-1]==5))
                        {
                            sthExist[enemy->x][enemy->y-1]=4;
                        }
                        if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                        {
                            sthExist[enemy->x][enemy->y]=0;
                        }
                        enemy->y=enemy->y-1;
                    }
                    else                               //看看横移动
                    {
                        if((player[0]->x)<(enemy->x)) //如果玩家1在enemy左面
                        {
                            if(sthExist[enemy->x-1][enemy->y]<6)//如果enemy左边没石头，炸弹,则向左移动
                            {
                                if((sthExist[enemy->x-1][enemy->y]==0)||(sthExist[enemy->x-1][enemy->y]==5))
                                {
                                    sthExist[enemy->x-1][enemy->y]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->x=enemy->x-1;
                            }
                        }
                        else                           //如果玩家1在enemy右面
                        {
                            if(sthExist[enemy->x+1][enemy->y]<6)//如果enemy右边没石头，炸弹,则向右移动
                            {
                                if((sthExist[enemy->x+1][enemy->y]==0)||(sthExist[enemy->x+1][enemy->y]==5))
                                {
                                    sthExist[enemy->x+1][enemy->y]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->x=enemy->x+1;
                            }
                        }
                    }
                }
                else                                    //玩家1在enemy下边
                {
                    if(sthExist[enemy->x][enemy->y+1]<6)//如果enemy下边没石头，炸弹,则向下移动
                    {
                        if((sthExist[enemy->x][enemy->y+1]==0)||(sthExist[enemy->x][enemy->y+1]==5))
                        {
                            sthExist[enemy->x][enemy->y+1]=4;
                        }
                        if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                        {
                            sthExist[enemy->x][enemy->y]=0;
                        }
                        enemy->y=enemy->y+1;
                    }
                    else                               //看看横向移动
                    {
                        if((player[0]->x)<(enemy->x)) //如果玩家1在enemy左面
                        {
                            if(sthExist[enemy->x-1][enemy->y]<6)//如果enemy左边没石头，炸弹,则向左移动
                            {
                                if((sthExist[enemy->x-1][enemy->y]==0)||(sthExist[enemy->x-1][enemy->y]==5))
                                {
                                    sthExist[enemy->x-1][enemy->y]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->x=enemy->x-1;
                            }
                        }
                        else                           //如果玩家1在enemy右面
                        {
                            if(sthExist[enemy->x+1][enemy->y]<6)//如果enemy右边没石头，炸弹,则向右移动
                            {
                                if((sthExist[enemy->x+1][enemy->y]==0)||(sthExist[enemy->x+1][enemy->y]==5))
                                {
                                    sthExist[enemy->x+1][enemy->y]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->x=enemy->x+1;
                            }
                        }
                    }
                }
            }
        }
        else                                            //距离玩家2较近，则向玩家2移动
        {
            if(x[1]>y[1])                               //横坐标更长，横向靠近
            {
                if((player[1]->x)<(enemy->x))           //玩家2在enemy左边
                {
                    if(sthExist[enemy->x-1][enemy->y]<6)//如果enemy左边没石头，炸弹,则向左移动
                    {
                        if((sthExist[enemy->x-1][enemy->y]==0)||(sthExist[enemy->x-1][enemy->y]==5))
                        {
                            sthExist[enemy->x-1][enemy->y]=4;
                        }
                        if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                        {
                            sthExist[enemy->x][enemy->y]=0;
                        }
                        enemy->x=enemy->x-1;
                    }
                    else                               //看看纵向移动
                    {
                        if((player[1]->y)<(enemy->y)) //如果玩家2在enemy上面
                        {
                            if(sthExist[enemy->x][enemy->y-1]<6)//如果enemy上边没石头，炸弹,则向上移动
                            {
                                if((sthExist[enemy->x][enemy->y-1]==0)||(sthExist[enemy->x][enemy->y-1]==5))
                                {
                                    sthExist[enemy->x][enemy->y-1]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->y=enemy->y-1;
                            }
                        }
                        else                           //如果玩家2在enemy下面
                        {
                            if(sthExist[enemy->x][enemy->y+1]<6)//如果enemy下边没石头，炸弹,则向下移动
                            {
                                if((sthExist[enemy->x][enemy->y+1]==0)||(sthExist[enemy->x][enemy->y+1]==5))
                                {
                                    sthExist[enemy->x][enemy->y+1]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->y=enemy->y+1;
                            }
                        }
                    }
                }
                else                                    //玩家2在enemy右边
                {
                    if(sthExist[enemy->x+1][enemy->y]<6)//如果enemy右边没石头，炸弹,则向右移动
                    {
                        if((sthExist[enemy->x+1][enemy->y]==0)||(sthExist[enemy->x+1][enemy->y]==5))
                        {
                            sthExist[enemy->x+1][enemy->y]=4;
                        }
                        if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                        {
                            sthExist[enemy->x][enemy->y]=0;
                        }
                        enemy->x=enemy->x+1;
                    }
                    else                               //看看纵向移动
                    {
                        if((player[1]->y)<(enemy->y)) //如果玩家2在enemy上面
                        {
                            if(sthExist[enemy->x][enemy->y-1]<6)//如果enemy上边没石头，炸弹,则向上移动
                            {
                                if((sthExist[enemy->x][enemy->y-1]==0)||(sthExist[enemy->x][enemy->y-1]==5))
                                {
                                    sthExist[enemy->x][enemy->y-1]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->y=enemy->y-1;
                            }
                        }
                        else                           //如果玩家2在enemy下面
                        {
                            if(sthExist[enemy->x][enemy->y+1]<6)//如果enemy下边没石头，炸弹,则向下移动
                            {
                                if((sthExist[enemy->x][enemy->y+1]==0)||(sthExist[enemy->x][enemy->y+1]==5))
                                {
                                    sthExist[enemy->x][enemy->y+1]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->y=enemy->y+1;
                            }
                        }
                    }
                }
            }
            else                                        //纵坐标更长，纵向靠近
            {
                if((player[1]->y)<(enemy->y))           //玩家2在enemy上边
                {
                    if(sthExist[enemy->x][enemy->y-1]<6)//如果enemy上边没石头，炸弹,则向左移动
                    {
                        if((sthExist[enemy->x][enemy->y-1]==0)||(sthExist[enemy->x][enemy->y-1]==5))
                        {
                            sthExist[enemy->x][enemy->y-1]=4;
                        }
                        if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                        {
                            sthExist[enemy->x][enemy->y]=0;
                        }
                        enemy->y=enemy->y-1;
                    }
                    else                               //看看横移动
                    {
                        if((player[1]->x)<(enemy->x)) //如果玩家2在enemy左面
                        {
                            if(sthExist[enemy->x-1][enemy->y]<6)//如果enemy左边没石头，炸弹,则向左移动
                            {
                                if((sthExist[enemy->x-1][enemy->y]==0)||(sthExist[enemy->x-1][enemy->y]==5))
                                {
                                    sthExist[enemy->x-1][enemy->y]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->x=enemy->x-1;
                            }
                        }
                        else                           //如果玩家2在enemy右面
                        {
                            if(sthExist[enemy->x+1][enemy->y]<6)//如果enemy右边没石头，炸弹,则向右移动
                            {
                                if((sthExist[enemy->x+1][enemy->y]==0)||(sthExist[enemy->x+1][enemy->y]==5))
                                {
                                    sthExist[enemy->x+1][enemy->y]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->x=enemy->x+1;
                            }
                        }
                    }
                }
                else                                    //玩家2在enemy下边
                {
                    if(sthExist[enemy->x][enemy->y+1]<6)//如果enemy下边没石头，炸弹,则向下移动
                    {
                        if((sthExist[enemy->x][enemy->y+1]==0)||(sthExist[enemy->x][enemy->y+1]==5))
                        {
                            sthExist[enemy->x][enemy->y+1]=4;
                        }
                        if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                        {
                            sthExist[enemy->x][enemy->y]=0;
                        }
                        enemy->y=enemy->y+1;
                    }
                    else                               //看看横向移动
                    {
                        if((player[1]->x)<(enemy->x)) //如果玩家2在enemy左面
                        {
                            if(sthExist[enemy->x-1][enemy->y]<6)//如果enemy左边没石头，炸弹,则向左移动
                            {
                                if((sthExist[enemy->x-1][enemy->y]==0)||(sthExist[enemy->x-1][enemy->y]==5))
                                {
                                    sthExist[enemy->x-1][enemy->y]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->x=enemy->x-1;
                            }
                        }
                        else                           //如果玩家2在enemy右面
                        {
                            if(sthExist[enemy->x+1][enemy->y]<6)//如果enemy右边没石头，炸弹,则向右移动
                            {
                                if((sthExist[enemy->x+1][enemy->y]==0)||(sthExist[enemy->x+1][enemy->y]==5))
                                {
                                    sthExist[enemy->x+1][enemy->y]=4;
                                }
                                if((sthExist[enemy->x][enemy->y]==4)||(sthExist[enemy->x][enemy->y]==5))
                                {
                                    sthExist[enemy->x][enemy->y]=0;
                                }
                                enemy->x=enemy->x+1;
                            }
                        }
                    }
                }
            }
        }
    }
}

