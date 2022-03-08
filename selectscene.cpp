#include <QTime>
#include <QTimer>
#include "selectscene.h"
#include "ui_selectscene.h"
#include "fightscene.h"
#include "util.h"

#define _CHAR_COUNT_ 5   //角色数

Selectscene::Selectscene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Selectscene)
{
    //设置界面
    ui->setupUi(this);

    //设置标题
    this->setWindowTitle("古龙角斗场");

    //初始化界面
    QStringList list;
    list << "刀哥" << "虎哥" << "百特曼" << "孙哥" << "龙卷风";
    ui->playerBox->addItems(list);
    ui->rivalBox->addItems(list);
    ui->rivalBox->setCurrentIndex(1);

    //初始化战斗场景
    Fightscene *fightscene = new Fightscene();

    //信号连接
    connect(ui->randomBotton, QPushButton::clicked, this, [=](){
        //随机分配角色
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        ui->playerBox->setCurrentIndex(qrand() % _CHAR_COUNT_);
        ui->rivalBox->setCurrentIndex(qrand() % _CHAR_COUNT_);
    });
    connect(ui->startButton, QPushButton::clicked, this, [=](){
        //布置战斗场景
        Util::setupScene(this, fightscene);
        //切换到战斗场景
        QTimer::singleShot(250, this, [=](){
            this->hide();
            fightscene->show();
            fightscene->start();
        });
    });
    connect(fightscene, Fightscene::sceneBack, this, [=](){
        //从战斗场景返回
        fightscene->hide();
        this->show();
    });
}

Selectscene::~Selectscene()
{
    delete ui;
}
