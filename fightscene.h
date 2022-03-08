#ifndef FIGHTSCENE_H
#define FIGHTSCENE_H

#include <QWidget>
#include <QSequentialAnimationGroup>
#include "creature.h"

namespace Ui { class Fightscene; }

class Creature;
class Skill;

class Fightscene : public QWidget
{
    Q_OBJECT
public:
    Fightscene(QWidget *parent = nullptr);
    ~Fightscene();
    void start();
    void disableAllButtons(bool boolean);
    void addInfo(QString str);
    void playShiftGroup();
    void playPlayerEffectGroup();
    void playRivalEffectGroup();
    void showGameOver();
    void setEffect(int type);
    void addSkill(Skill *skill);
    void showSkillDesc(int index);

private:
    friend class Util;

    Ui::Fightscene *ui;

    Creature *player; //玩家对象
    Creature *rival;  //对手对象

    int round;
    bool isOver;

    QSequentialAnimationGroup *shiftGroup;
    QSequentialAnimationGroup *playerEffectGroup;
    QSequentialAnimationGroup *rivalEffectGroup;

    QStringList skillNameList;
    QStringList skillDescList;

signals:
    void sceneBack();   //场景返回信号
    void playerEnd();   //玩家结束信号
    void rivalEnd();    //对手结束信号
    void gameOver();    //游戏结束信号
};
#endif  //FIGHTSCENE_H
