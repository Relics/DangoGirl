#include"preFace.h"

void preFace::closeStart()
{
    delete startLabel;
}

void preFace::closeHelp()
{
    delete helpLabel;
    start();
}

void preFace::closeInfor()
{
    delete inforLabel;
    start();
}

void preFace::closeMode()
{
    delete ModeLabel;
    start();
}

void preFace::Role2()
{
    delete ModeLabel;
    RoleLabel1=new QLabel;
    RoleLabel1->setScaledContents(true);
    RoleLabel1->move((QApplication::desktop()->width() -   RoleLabel1->width())/2, (QApplication::desktop()->height() -   RoleLabel1->height())/2);
    RoleLabel1->setPixmap(QPixmap("./images/selectplayer1.jpg"));//背景图片待定
    RoleLabel1->show();
    RoleButton1=new QPushButton();
    RoleButton2=new QPushButton();
    RoleButton3=new QPushButton();
    RoleButton4=new QPushButton();
    RoleButton1->setIcon(QIcon("./images/001.png"));
    RoleButton1->setIconSize(QSize(120, 240));
    RoleButton1->setStyleSheet("background:transparent");
    RoleButton2->setIcon(QIcon("./images/002.png"));
    RoleButton2->setIconSize(QSize(120, 240));
    RoleButton2->setStyleSheet("background:transparent");
    RoleButton3->setIcon(QIcon("./images/003.png"));
    RoleButton3->setIconSize(QSize(120, 240));
    RoleButton3->setStyleSheet("background:transparent");
    RoleButton4->setIcon(QIcon("./images/004.png"));
    RoleButton4->setIconSize(QSize(120, 240));
    RoleButton4->setStyleSheet("background:transparent");
    returnButtton=new QPushButton();
    returnButtton->setIcon(QIcon("./images/Return.png"));//添加图
    returnButtton->setIconSize(QSize(150, 150));
    returnButtton->setStyleSheet("background:transparent");
    QHBoxLayout *layout1=new QHBoxLayout;
    QHBoxLayout *layout2=new QHBoxLayout;
    QVBoxLayout *layout3=new QVBoxLayout;
    layout1->addWidget(RoleButton1);
    layout1->addWidget(RoleButton2);
    layout1->addWidget(RoleButton3);
    layout1->addWidget(RoleButton4);
    layout2->addStretch();
    layout2->addWidget(returnButtton);
    layout2->addStretch();
    layout3->addStretch();
    layout3->addLayout(layout1);
    layout3->addLayout(layout2);
    RoleLabel1->setLayout(layout3);
    RoleButton1->connect(RoleButton1,SIGNAL(clicked()),this,SLOT(role1_1choosed()));
    RoleButton2->connect(RoleButton2,SIGNAL(clicked()),this,SLOT(role1_2choosed()));
    RoleButton3->connect(RoleButton3,SIGNAL(clicked()),this,SLOT(role1_3choosed()));
    RoleButton4->connect(RoleButton4,SIGNAL(clicked()),this,SLOT(role1_4choosed()));
    returnButtton->connect(returnButtton,SIGNAL(clicked()),this,SLOT(closeRole1()));
}

void preFace::closeRole1()
{
    delete RoleLabel1;
    start();
}

void preFace::closeRole2()
{
    delete RoleLabel2;
    start();
}

void preFace::go()
{
    music1.setMedia(QUrl::fromLocalFile("./music/love.wma"));
    //music1 = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource("./music/love.wma"));
    music1.play();
    start();
}

void preFace::start()
{
    startLabel=new QLabel;//创建开始界面，包含4个按钮
    startLabel->setScaledContents(true);
    startLabel->move((QApplication::desktop()->width() -  startLabel->width())/2, (QApplication::desktop()->height() -  startLabel->height())/2);
    startLabel->setPixmap(QPixmap("./images/background2.jpg"));//背景图片待定
    startButton=new QPushButton();//创建START按钮，待添加链接、事件
    startButton->setIcon(QIcon("./images/start.png"));//添加图
    startButton->setIconSize(QSize(226, 226));
    startButton->setStyleSheet("background:transparent");

    helpButton=new QPushButton();//创建HELP按钮，待添加链接、事件
    helpButton->setIcon(QIcon("./images/Help.png"));//添加图
    helpButton->setIconSize(QSize(226, 226));
    helpButton->setStyleSheet("background:transparent");
    inforButton=new QPushButton();//创建HELP按钮，待添加链接、事件
    inforButton->setIcon(QIcon("./images/About.png"));//添加图
    inforButton->setIconSize(QSize(226, 226));
    inforButton->setStyleSheet("background:transparent");
    returnButtton=new QPushButton();//创建QUIT按钮，待添加事件  inforButton=new QPushButton();//创建HELP按钮，待添加链接、事件
    returnButtton->setIcon(QIcon("./images/Quit.png"));//添加图
    returnButtton->setIconSize(QSize(226, 226));
    returnButtton->setStyleSheet("background:transparent");
    //connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));//QWidget中的槽  默认隐藏窗口但不删除
    QHBoxLayout *startLayout=new QHBoxLayout;//QHBoxLayout横向布局  QV竖向  可嵌套
    QVBoxLayout *startLayout1=new QVBoxLayout;
    QVBoxLayout *startLayout2=new QVBoxLayout;
    startLayout1->addStretch();//弹簧函数，挤压已经加入的项目，占据空白
    startLayout1->addWidget(startButton);
    startLayout1->addWidget(helpButton);
    startLayout1->addStretch();//弹簧函数，挤压已经加入的项目，占据空白
    startLayout2->addStretch();//弹簧函数，挤压已经加入的项目，占据空白
    startLayout2->addWidget(inforButton);
    startLayout2->addWidget(returnButtton);
    startLayout2->addStretch();//弹簧函数，挤压已经加入的项目，占据空白
    startLayout->addStretch();//弹簧函数，挤压已经加入的项目，占据空白
    startLayout->addLayout(startLayout1);
    startLayout->addStretch();//弹簧函数，挤压已经加入的项目，占据空白
    startLayout->addLayout(startLayout2);
    startLayout->addStretch();//弹簧函数，挤压已经加入的项目，占据空白
    startLabel->setLayout(startLayout);
    startButton->show();
    helpButton->show();
    inforButton->show();
    returnButtton->show();
    startLabel->show();
    startButton->connect(startButton,SIGNAL(clicked()),this,SLOT(Mode()));
    helpButton->connect(helpButton,SIGNAL(clicked()),this,SLOT(help()));
    inforButton->connect(inforButton,SIGNAL(clicked()),this,SLOT(infor()));
    returnButtton->connect(returnButtton,SIGNAL(clicked()),this,SLOT(closeStart()));
}

void preFace::help()
{
    delete startLabel;
    helpLabel=new QLabel;
    helpLabel->setScaledContents(true);
    helpLabel->move((QApplication::desktop()->width() -   helpLabel->width())/2, (QApplication::desktop()->height() -   helpLabel->height())/2);
    helpLabel->setPixmap(QPixmap("./images/help.jpg"));//背景图片待定
    helpLabel->show();
    returnButtton=new QPushButton();
    returnButtton->setIcon(QIcon("./images/Return.png"));//添加图
    returnButtton->setIconSize(QSize(150, 150));
    returnButtton->setStyleSheet("background:transparent");
    /*QFile file("./document/help.txt");
    QLabel *label=new QLabel();
    label->setScaledContents(true);
    file.open(QIODevice::ReadOnly|QFile::Text);
    QTextStream in(&file);
    label->setText(in.readAll());
    label->show();*/
    returnButtton->show();
    QVBoxLayout *layout=new QVBoxLayout;
    QHBoxLayout *layout1=new QHBoxLayout;
    layout->addStretch();
    //layout->addWidget(label);
    layout->addLayout(layout1);
    layout1->addStretch();
    layout1->addStretch();
    layout1->addStretch();
    layout1->addWidget(returnButtton);
    helpLabel->setLayout(layout);
    layout1->addStretch();
    returnButtton->connect(returnButtton,SIGNAL(clicked()),this,SLOT(closeHelp()));
}

void preFace::infor()
{
    delete startLabel;
    inforLabel=new QLabel;
    inforLabel->setScaledContents(true);
    inforLabel->move((QApplication::desktop()->width() -  inforLabel->width())/2, (QApplication::desktop()->height() -  inforLabel->height())/2);
    inforLabel->setPixmap(QPixmap("./images/info.jpg"));//背景图片待定
    inforLabel->show();
    returnButtton=new QPushButton();
    returnButtton->setIcon(QIcon("./images/Return.png"));//添加图
    returnButtton->setIconSize(QSize(226, 226));
    returnButtton->setStyleSheet("background:transparent");
    /*QFile file("./document/infor.txt");
    QLabel *label=new QLabel();
    label->setScaledContents(true);
    file.open(QIODevice::ReadOnly|QFile::Text);
    QTextStream in(&file);
    label->setText(in.readAll());
    label->show();*/
    returnButtton->show();
    QVBoxLayout *layout=new QVBoxLayout;
    QHBoxLayout *layout1=new QHBoxLayout;
    layout->addStretch();
    //layout->addWidget(label);
    layout->addLayout(layout1);
    layout1->addStretch();
    layout1->addWidget(returnButtton);
    layout1->addStretch();
    inforLabel->setLayout(layout);
   returnButtton->connect(returnButtton,SIGNAL(clicked()),this,SLOT(closeInfor()));
}

void preFace::Mode()
{
    delete startLabel;
    ModeLabel=new QLabel;
    ModeLabel->setScaledContents(true);
    ModeLabel->move((QApplication::desktop()->width() -  ModeLabel->width())/2, (QApplication::desktop()->height() -  ModeLabel->height())/2);
    ModeLabel->setPixmap(QPixmap("./images/background2.jpg"));//背景图片待定
    ModeLabel->show();
    QLabel *label=new QLabel("请选择游戏模式：");
    label->move(200,50);
    ModeButton1=new QPushButton();
    ModeButton1->setIcon(QIcon("./images/Leisure.png"));//添加图
    ModeButton1->setIconSize(QSize(166, 166));//116
    ModeButton1->setStyleSheet("background:transparent");
    ModeButton2=new QPushButton();
    ModeButton2->setIcon(QIcon("./images/Entertainment.png"));//添加图
    ModeButton2->setIconSize(QSize(166, 166));
    ModeButton2->setStyleSheet("background:transparent");
    ModeButton3=new QPushButton();
    ModeButton3->setIcon(QIcon("./images/Hell.png"));//添加图
    ModeButton3->setIconSize(QSize(166, 166));
    ModeButton3->setStyleSheet("background:transparent");
    ModeButton4=new QPushButton();
    ModeButton4->setIcon(QIcon("./images/Ghost.png"));//添加图
    ModeButton4->setIconSize(QSize(135, 135));
    ModeButton4->setStyleSheet("background:transparent");

    returnButtton=new QPushButton();
    returnButtton->setIcon(QIcon("./images/Return.png"));//添加图
    returnButtton->setIconSize(QSize(140, 140));
    returnButtton->setStyleSheet("background:transparent");

    ModeButton1->show();
    ModeButton2->show();
    ModeButton3->show();
    QHBoxLayout *layout1=new QHBoxLayout;
    QHBoxLayout *layout2=new QHBoxLayout;
    QVBoxLayout *layout3=new QVBoxLayout;
    layout1->addStretch();
    layout1->addWidget(ModeButton1);
    layout1->addStretch();
    layout1->addWidget(ModeButton2);
    layout1->addStretch();
    layout2->addStretch();
    layout2->addWidget(ModeButton3);
    layout2->addStretch();
    layout2->addWidget(ModeButton4);
    layout2->addStretch();
    layout3->addLayout(layout1);
    layout3->addLayout(layout2);
    layout3->addWidget(returnButtton);
    ModeLabel->setLayout(layout3);
    ModeButton1->connect(ModeButton1,SIGNAL(clicked()),this,SLOT(mode1()));
    ModeButton2->connect(ModeButton2,SIGNAL(clicked()),this,SLOT(mode2()));
    ModeButton3->connect(ModeButton3,SIGNAL(clicked()),this,SLOT(mode3()));
    ModeButton4->connect(ModeButton4,SIGNAL(clicked()),this,SLOT(mode4()));
    returnButtton->connect(returnButtton,SIGNAL(clicked()),this,SLOT(closeMode()));
}

void preFace::role2()
{
    RoleLabel2=new QLabel;
    RoleLabel2->setScaledContents(true);
    RoleLabel2->move((QApplication::desktop()->width() -  RoleLabel2->width())/2, (QApplication::desktop()->height() - RoleLabel2->height())/2);
    RoleLabel2->setPixmap(QPixmap("./images/selectplayer2.jpg"));//背景图片待定
    RoleLabel2->show();
    RoleButton1=new QPushButton();
    RoleButton2=new QPushButton();
    RoleButton3=new QPushButton();
    RoleButton4=new QPushButton();
    RoleButton1->setIcon(QIcon("./images/001.png"));
    RoleButton1->setIconSize(QSize(120, 240));
    RoleButton1->setStyleSheet("background:transparent");
    RoleButton2->setIcon(QIcon("./images/002.png"));
    RoleButton2->setIconSize(QSize(120, 240));
    RoleButton2->setStyleSheet("background:transparent");
    RoleButton3->setIcon(QIcon("./images/003.png"));
    RoleButton3->setIconSize(QSize(120, 240));
    RoleButton3->setStyleSheet("background:transparent");
    RoleButton4->setIcon(QIcon("./images/004.png"));
    RoleButton4->setIconSize(QSize(120, 240));
    RoleButton4->setStyleSheet("background:transparent");
    returnButtton=new QPushButton();
    returnButtton->setIcon(QIcon("./images/Return.png"));//添加图
    returnButtton->setIconSize(QSize(150, 150));
    returnButtton->setStyleSheet("background:transparent");
    QHBoxLayout *layout1=new QHBoxLayout;
    QHBoxLayout *layout2=new QHBoxLayout;
    QVBoxLayout *layout3=new QVBoxLayout;
    layout1->addWidget(RoleButton1);
    layout1->addWidget(RoleButton2);
    layout1->addWidget(RoleButton3);
    layout1->addWidget(RoleButton4);
    layout2->addStretch();
    layout2->addWidget(returnButtton);
    layout2->addStretch();
    layout3->addStretch();
    layout3->addLayout(layout1);
    layout3->addLayout(layout2);
    RoleLabel1->setLayout(layout3);
    RoleButton1->connect(RoleButton1,SIGNAL(clicked()),this,SLOT(role2_1choosed()));
    RoleButton2->connect(RoleButton2,SIGNAL(clicked()),this,SLOT(role2_2choosed()));
    RoleButton3->connect(RoleButton3,SIGNAL(clicked()),this,SLOT(role2_3choosed()));
    RoleButton4->connect(RoleButton4,SIGNAL(clicked()),this,SLOT(role2_4choosed()));
    returnButtton->connect(returnButtton,SIGNAL(clicked()),this,SLOT(closeRole2()));
}


void preFace::role1choosed()
{
    delete RoleLabel1;
}

void preFace::role2choosed()
{
    delete RoleLabel1;
}

void preFace::role3choosed()
{
    delete RoleLabel1;
}

void preFace::role4choosed()
{
    delete RoleLabel1;
}

void preFace::role1_1choosed()
{
    delete RoleLabel1;
    player1 = 1;

    role2();
    RoleButton1->setEnabled(false);
}

void preFace::role1_2choosed()
{
    delete RoleLabel1;
    player1 = 2;

    role2();
    RoleButton2->setEnabled(false);
}

void preFace::role1_3choosed()
{
    delete RoleLabel1;
    player1 = 3;

    role2();
    RoleButton3->setEnabled(false);
}

void preFace::role1_4choosed()
{
    delete RoleLabel1;
    player1 = 4;

    role2();
    RoleButton4->setEnabled(false);
}

void preFace::role2_1choosed()
{
    player2 = 1;

    delete RoleLabel2;
    gameStart();
}

void preFace::role2_2choosed()
{
    player2 = 2;

    delete RoleLabel2;
    gameStart();
}

void preFace::role2_3choosed()
{
    player2 = 3;

    delete RoleLabel2;
    gameStart();
}

void preFace::role2_4choosed()
{
    player2 = 4;

    delete RoleLabel2;
    gameStart();
}

void preFace::mode1()
{
    mode = 1;
    Role2();
}

void preFace::mode2()
{
    mode = 2;
    Role2();
}

void preFace::mode3()
{
    mode =3;
    Role2();
}

void preFace::mode4()
{
    mode =4;
    Role2();
}

void preFace::gameStart()
{

    QSplashScreen *splash1=new QSplashScreen;
    splash1->setPixmap(QPixmap("./images/00003.jpg"));
    splash1->show();
    for(int i=0;i<150;i++)
    {
        splash1->repaint();
    }
    delete splash1;

    QSplashScreen *splash2=new QSplashScreen;
    splash2->setPixmap(QPixmap("./images/00002.jpg"));
    splash2->show();
    for(int i=0;i<150;i++)
    {
        splash2->repaint();
    }
    delete splash2;

    QSplashScreen *splash3=new QSplashScreen;
    splash3->setPixmap(QPixmap("./images/00001.jpg"));
    splash3->show();
    for(int i=0;i<150 ;i++)
    {
        splash3->repaint();
    }
    delete splash3;

    music1.stop();
    bombMan.setmode(mode);
    bombMan.setplayer1(player1);
    bombMan.setplayer2(player2);
    bombMan.setWindowTitle("DangoGirl");  //修改主界面名称
    bombMan.show();                          //显示主界面
    bombMan.move((QApplication::desktop()->width() - bombMan.width())/2,
                 (QApplication::desktop()->height() - bombMan.height())/2);
    bombMan.gameStart();
}

void preFace::gameEnd()
{
    music2.setMedia(QUrl::fromLocalFile("./music/Ending.wma"));
    //music2 = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource("./music/Ending.wma"));
    music2.play();

    EndLabel=new QLabel;
    EndLabel->setScaledContents(true);
    EndLabel->move((QApplication::desktop()->width() -  EndLabel->width())/2, (QApplication::desktop()->height() - EndLabel->height())/2);
    EndLabel->setPixmap(QPixmap("./images/Qexit.jpg"));//背景图片待定
    EndLabel->show();
    yesButton=new QPushButton();
    yesButton->setIcon(QIcon("./images/yes.png"));//添加图
    yesButton->setIconSize(QSize(200, 200));
    yesButton->setStyleSheet("background:transparent");
    noButton=new QPushButton();
    noButton->setIcon(QIcon("./images/No.png"));//添加图
    noButton->setIconSize(QSize(200, 200));
    noButton->setStyleSheet("background:transparent");
    QHBoxLayout *layout1=new QHBoxLayout;
    QVBoxLayout *layout2=new QVBoxLayout;
    layout1->addStretch();
    layout1->addWidget(yesButton);
    layout1->addWidget(noButton);
    layout2->addStretch();
    layout2->addLayout(layout1);
    EndLabel->setLayout(layout2);
    yesButton->connect(yesButton,SIGNAL(clicked()),this,SLOT(restart()));
    noButton->connect(noButton,SIGNAL(clicked()),this,SLOT(closeGameEnd()));
}

void preFace::restart()
{
    music2.stop();
    delete EndLabel;
    QSplashScreen *splash1=new QSplashScreen;
    splash1->setPixmap(QPixmap("./images/00003.jpg"));
    splash1->show();
    for(int i=0;i<150;i++)
    {
        splash1->repaint();
    }
    delete splash1;

    QSplashScreen *splash2=new QSplashScreen;
    splash2->setPixmap(QPixmap("./images/00002.jpg"));
    splash2->show();
    for(int i=0;i<150;i++)
    {
        splash2->repaint();
    }
    delete splash2;

    QSplashScreen *splash3=new QSplashScreen;
    splash3->setPixmap(QPixmap("./images/00001.jpg"));
    splash3->show();
    for(int i=0;i<150;i++)
    {
        splash3->repaint();
    }
    delete splash3;
    bombMan.setWindowTitle("DangoGirl");     //修改主界面名称
    bombMan.show();                          //显示主界面
    bombMan.move((QApplication::desktop()->width() - bombMan.width())/2,
                 (QApplication::desktop()->height() - bombMan.height())/2);
    bombMan.gameStart();
}

void preFace::closeGameEnd()
{
     delete EndLabel;
     music2.stop();
     go();
}

