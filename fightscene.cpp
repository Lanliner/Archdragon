#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <QMessageBox>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QTimer>
#include "creature.h"
#include "fightscene.h"
#include "ui_fightscene.h"
#include "skillcard.h"
#include "util.h"

Fightscene::Fightscene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Fightscene)
{
    //设置界面
    ui->setupUi(this);

    //设置窗口标题
    this->setWindowTitle("古龙角斗场");

    //初始化界面
    ui->background->setScaledContents(true);    //图片缩放适应
    ui->effectLabel->setScaledContents(true);
    ui->playerEffectLabel->setScaledContents(true);
    ui->rivalEffectLabel->setScaledContents(true);

    //动画
    shiftGroup = Util::setShiftEffect(ui->effectLabel);   //位移效果动画
    playerEffectGroup = Util::setCharEffect(ui->playerEffectLabel);  //角色效果动画
    rivalEffectGroup = Util::setCharEffect(ui->rivalEffectLabel);

    //信号连接
    connect(ui->attackButton, QPushButton::clicked, this, [=](){    //攻击按钮
        disableAllButtons(true);
        player->attack();
    });
    connect(ui->magicAttackButton, QPushButton::clicked, this, [=](){    //魔法攻击按钮
        disableAllButtons(true);
        if(player->magicAttack() == false)
            disableAllButtons(false);
    });
    connect(ui->skillButton, QPushButton::clicked, this, [=](){ //技能按钮
        ui->infoLabel->setVisible(!ui->infoLabel->isVisible());
        ui->skillLabel->setVisible(!ui->skillLabel->isVisible());
        ui->infoList->setVisible(!ui->infoList->isVisible());
        ui->skillList->setVisible(!ui->infoList->isVisible());

        if(ui->skillList->isVisible()) {
            disableAllButtons(true);
            ui->skillButton->setDisabled(false);
        } else {
            disableAllButtons(false);
            ui->skillDesc->setVisible(false);
        }
    });
    connect(ui->skillList, QListWidget::itemClicked, this, [=](){   //单击技能
        ui->skillDesc->setVisible(true);
        ui->skillDesc->setText(skillDescList.at(ui->skillList->currentRow()));
    });
    connect(ui->skillList, QListWidget::itemDoubleClicked, this, [=](){   //双击技能
        int index = ui->skillList->currentRow();
        if(player->launchSkill(index) == true) {
            disableAllButtons(true);
            ui->infoLabel->setVisible(true);
            ui->skillLabel->setVisible(false);
            ui->infoList->setVisible(true);
            ui->skillList->setVisible(false);
            ui->skillDesc->setVisible(false);
            ui->skillButton->setChecked(false);

            ui->skillList->takeItem(ui->skillList->currentRow());
            skillNameList.removeAt(index);
            skillDescList.removeAt(index);
        }
    });
    connect(ui->defendButton, QPushButton::clicked, this, [=](){    //防御按钮
        disableAllButtons(true);
        player->defend();
    });
    connect(ui->dodgeButton, QPushButton::clicked, this, [=](){ //闪避按钮
        disableAllButtons(true);
        player->dodge();
    });
    connect(ui->surrenderButton, QPushButton::clicked, this, [=](){ //投降按钮
        QTimer::singleShot(250, this, [=](){
            emit this->sceneBack();
        });
    });
    connect(this, Fightscene::playerEnd, this, [=](){   //玩家回合结束，对手回合开始
        ui->effectLabel->setPixmap(QPixmap(":/resource/attack.png"));
        shiftGroup->setDirection(QAbstractAnimation::Backward);
        rival->traverseBuff();
        rival->autoAct();

    });
    connect(this, Fightscene::rivalEnd, this, [=](){   //对手回合结束，玩家回合开始
        ui->roundText->setText(QString::number(++round));
        addInfo(QString::asprintf("----< 第 %d 回合开始 >----", round));
        shiftGroup->setDirection(QAbstractAnimation::Forward);
        disableAllButtons(false);
        player->traverseBuff();
        Util::getRandomSkill(player);   //获得新技能
    });
    connect(this, Fightscene::gameOver, this, Fightscene::showGameOver);    //游戏结束
}

Fightscene::~Fightscene()
{
    delete ui;
}

void Fightscene::disableAllButtons(bool boolean)
{
    if(boolean) {
        ui->attackButton->setDisabled(true);
        ui->magicAttackButton->setDisabled(true);
        ui->skillButton->setDisabled(true);
        ui->defendButton->setDisabled(true);
        ui->dodgeButton->setDisabled(true);
        ui->surrenderButton->setDisabled(true);
    } else {
        ui->attackButton->setDisabled(false);
        ui->magicAttackButton->setDisabled(false);
        ui->skillButton->setDisabled(false);
        ui->defendButton->setDisabled(false);
        ui->dodgeButton->setDisabled(false);
        ui->surrenderButton->setDisabled(false);
    }
}

void Fightscene::start()
{
    round = 0;
    disableAllButtons(true);
    addInfo(player->getPrologue());
    shiftGroup->setDirection(QAbstractAnimation::Forward);
    ui->effectLabel->setPixmap(QPixmap(":/resource/start.png"));
    playShiftGroup();
    QTimer::singleShot(2000, this, [=](){
        ui->roundText->setText(QString::number(++round));
        addInfo(QString::asprintf("----< 第 %d 回合开始 >----", round));
        disableAllButtons(false);
        Util::getRandomSkill(player);
    });

}

void Fightscene::addInfo(QString str)
{
    ui->infoList->addItem(str);
    ui->infoList->scrollToBottom();
}

void Fightscene::playShiftGroup()
{
    shiftGroup->start();
}

void Fightscene::playPlayerEffectGroup()
{
    playerEffectGroup->start();
}

void Fightscene::playRivalEffectGroup()
{
    rivalEffectGroup->start();
}

void Fightscene::showGameOver()
{
    QString title;
    QString content;
    if(player->getHp() == 0)
        title = "惜败";
    else
        title = "胜利";
    QMessageBox messageBox(QMessageBox::NoIcon, title, "是否再来一局？", QMessageBox::Yes | QMessageBox::No, NULL); ;
    int result=messageBox.exec();
    if(result == QMessageBox::Yes)
        emit sceneBack();
    else
        close();
}

void Fightscene::setEffect(int type)
{
    switch (type) {
    case 1: //普通攻击
        ui->effectLabel->setPixmap(QPixmap(":/resource/attack.png"));
        break;
    case 2: //魔法攻击
        ui->effectLabel->setPixmap(QPixmap(":/resource/fireball.png"));
        break;
    default:
        break;
    }
}

void Fightscene::addSkill(Skill *skill)
{
    ui->skillList->addItem(skill->getName());
    skillNameList.push_back(skill->getName());
    skillDescList.push_back(skill->getDescription());
}

