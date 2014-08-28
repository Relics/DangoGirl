#include<QApplication>
#include<QMessageBox>
#include<QSplashScreen>
#include<QPixmap>
#include<QDesktopWidget>
#include<QDateTime>
#include<QPushButton>
#include<QLayout>
#include<QLabel>
#include<QTextCodec>

#include"bombman.h"
#include"preFace.h"


int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    //Phonon::MediaObject *musicLogo;
    QMediaPlayer musicLogo;
    musicLogo.setMedia(QUrl::fromLocalFile("./music/logo.wma"));
    //musicLogo= Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource("./music/logo.wma"));
    musicLogo.play();

    //设置程序启动画面1
    QSplashScreen *splash=new QSplashScreen;
    splash->setPixmap(QPixmap("./images/startPic.jpg"));
    //（待修改）是可以用gif格式插入动画的，但是不理解为什么GIF格式不能在程序里刷新
    splash->show();
    for(int i=0;i<500;i++)
    {
        splash->repaint();
    }
    //设计启动画面延迟
   QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do{
        now=QDateTime::currentDateTime();
    } while (n.secsTo(now)<=1);//3为需要延时的秒数*/

    delete splash;

    //通过一定数量图片来模拟gif
    QSplashScreen *splash2=new QSplashScreen;
    splash2->setPixmap(QPixmap("./images/love/loveF0.jpg"));
    //（待修改）是可以用gif格式插入动画的，但是不理解为什么GIF格式不能在程序里刷新
    splash2->show();
    for(int i=0;i<100;i++)
    {
        splash2->repaint();
    }

    splash2->setPixmap(QPixmap("./images/love/loveF00.jpg"));
    //（待修改）是可以用gif格式插入动画的，但是不理解为什么GIF格式不能在程序里刷新
    splash2->show();
    for(int i=0;i<50;i++)
    {
        splash2->repaint();
    }


    splash2->setPixmap(QPixmap("./images/love/loveF1.jpg"));
    //（待修改）是可以用gif格式插入动画的，但是不理解为什么GIF格式不能在程序里刷新
    splash2->show();
    for(int i=0;i<20;i++)
    {
        splash2->repaint();
    }


    splash2->setPixmap(QPixmap("./images/love/loveF2.jpg"));
    //（待修改）是可以用gif格式插入动画的，但是不理解为什么GIF格式不能在程序里刷新
    splash2->show();
    for(int i=0;i<20;i++)
    {
        splash2->repaint();
    }


    splash2->setPixmap(QPixmap("./images/love/loveF3.jpg"));
    //（待修改）是可以用gif格式插入动画的，但是不理解为什么GIF格式不能在程序里刷新
    splash2->show();
    for(int i=0;i<20;i++)
    {
        splash2->repaint();
    }


    splash2->setPixmap(QPixmap("./images/love/loveF4.jpg"));
    //（待修改）是可以用gif格式插入动画的，但是不理解为什么GIF格式不能在程序里刷新
    splash2->show();
    for(int i=0;i<20;i++)
    {
        splash2->repaint();
    }


    splash2->setPixmap(QPixmap("./images/love/loveF5.jpg"));
    //（待修改）是可以用gif格式插入动画的，但是不理解为什么GIF格式不能在程序里刷新
    splash2->show();
    for(int i=0;i<20;i++)
    {
        splash2->repaint();
    }


    splash2->setPixmap(QPixmap("./images/love/loveF6.jpg"));
    //（待修改）是可以用gif格式插入动画的，但是不理解为什么GIF格式不能在程序里刷新
    splash2->show();
    for(int i=0;i<20;i++)
    {
        splash2->repaint();
    }


    splash2->setPixmap(QPixmap("./images/love/loveF6.jpg"));
    //（待修改）是可以用gif格式插入动画的，但是不理解为什么GIF格式不能在程序里刷新
    splash2->show();
    for(int i=0;i<20;i++)
    {
        splash2->repaint();
    }

    //设计启动画面延迟
    QDateTime n2=QDateTime::currentDateTime();
    QDateTime now2;
    do{
        now2=QDateTime::currentDateTime();
    } while (n2.secsTo(now2)<=1);//1为需要延时的秒数

    musicLogo.stop();
    delete splash2;


    preFace *face=new preFace;
    face->go();

    //显示游戏画面
    /*BombMan bombMan;
    bombMan.setWindowTitle("CrazyBombMan");  //修改主界面名称
    bombMan.show();                          //显示主界面
    bombMan.move((QApplication::desktop()->width() - bombMan.width())/2,
                 (QApplication::desktop()->height() - bombMan.height())/2);*/
    /*
    splash->finish(&startSplash);//当主窗口启动后，启动画面隐藏
    delete splash;

    startSplash->finish(&bombMan);//当主窗口启动后，启动画面隐藏
    delete startSplash;
    */
    return app.exec();
}
