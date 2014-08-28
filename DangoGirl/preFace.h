#ifndef PREFACE_H
#define PREFACE_H

#include<QApplication>
#include<QDesktopWidget>
#include<QDateTime>
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QLayout>
#include<QMessageBox>
#include<QSplashScreen>
//#include<MediaObject>
#include<QPixmap>
#include<QFile>
#include<QtGui>
#include"bombman.h"
#include <QMediaPlayer>

/*标签类*/
//class QLabel;
/*显示数字类*/
class QLCDNumber;
/*按钮类*/
class QPushButton;
/*定义器类*/
class QTimer;
/*声音类*/
class QSound;
/*游戏类类定义*/

class preFace:public QLabel
{
        Q_OBJECT
public:
        void go();
        void start();
        void role2();
        void Role2();
        void gameStart();
        void gameEnd();
        void ready();
private slots:
    void closeStart();
    void closeHelp();
    void closeInfor();
    void closeMode();
    void closeRole1();
    void closeRole2();
    void help();
    void infor();
    void Mode();
   void role1_1choosed();
   void role1_2choosed();
   void role1_3choosed();
   void role1_4choosed();
   void role2_1choosed();
   void role2_2choosed();
   void role2_3choosed();
   void role2_4choosed();
   void role1choosed();
   void role2choosed();
   void role3choosed();
   void role4choosed();
   void mode1();
   void mode2();
   void mode3();
   void mode4();
   void restart();
   void closeGameEnd();


private:
    QLabel *startLabel;
    QLabel *helpLabel;
    QLabel *inforLabel;
    QLabel *ModeLabel;
    QLabel *RoleLabel1;
    QLabel *RoleLabel2;
    QLabel *EndLabel;
    QPushButton *startButton;
    QPushButton *helpButton;
    QPushButton *inforButton;
    QPushButton *quitButton;
    QPushButton *ModeButton1;
    QPushButton *ModeButton2;
    QPushButton *ModeButton3;
    QPushButton *ModeButton4;
    QPushButton *RoleButton1;
    QPushButton *RoleButton2;
    QPushButton *RoleButton3;
    QPushButton *RoleButton4;
    QPushButton *yes;

    QMediaPlayer music1;
    QMediaPlayer music2;

    QPushButton *returnButtton;
    QPushButton *yesButton;
    QPushButton *noButton;

    QLabel *ReadyLabel;
    QPushButton *goButton;

public:
    BombMan bombMan;

public:
    int mode;
    int player1;
    int player2=1;
};

#endif // PREFACE_H
