#ifndef UTIL_H
#define UTIL_H

#include <QLabel>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QTime>
#include "selectscene.h"
#include "ui_selectscene.h"
#include "fightscene.h"
#include "ui_fightscene.h"
#include "creature.h"
#include "skill.h"

#define _LOC_COUNT_ 3   //场景数

class Util
{
public:
    static void setupScene(Selectscene *selectscene, Fightscene *fightscene)
    {
        //设置角色
        setupChar(fightscene->player, selectscene->ui->playerBox->currentIndex());

        fightscene->player->setScene(
                                        fightscene,
                                        fightscene->ui->playerPic,
                                        fightscene->ui->playerEffectLabel,
                                        fightscene->ui->playerHealthBar,
                                        fightscene->ui->playerHP,
                                        fightscene->ui->playerMagicBar,
                                        fightscene->ui->playerMP
        );
        fightscene->ui->playerPic->setScaledContents(true);
        fightscene->player->tagPlayer();

        setupChar(fightscene->rival, selectscene->ui->rivalBox->currentIndex());
        fightscene->rival->setScene(fightscene, fightscene->ui->rivalPic, fightscene->ui->rivalEffectLabel, fightscene->ui->rivalHealthBar, fightscene->ui->rivalHP);
        fightscene->ui->rivalPic->setScaledContents(true);

        //设置对手
        fightscene->player->setEnemy(fightscene->rival);
        fightscene->rival->setEnemy(fightscene->player);

        //设置背景
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        fightscene->ui->background->setPixmap(QPixmap(QString(":/resource/location_") + QString::number(qrand() % _LOC_COUNT_ + 1)));

        //设置可见
        fightscene->ui->skillLabel->setVisible(false);
        fightscene->ui->skillList->setVisible(false);
        fightscene->ui->skillDesc->setVisible(false);

        //设置名称
        fightscene->ui->playerName->setText(selectscene->ui->nameEdit->text());
        fightscene->ui->rivalName->setText(fightscene->rival->getName());

        //设置HP、MP条
        setupBar(fightscene);

        //清空战斗记录
        fightscene->ui->infoList->clear();

        //清空技能列表
        fightscene->ui->skillList->clear();
        fightscene->skillNameList.clear();
        fightscene->skillDescList.clear();

        //按钮初始化
        fightscene->disableAllButtons(false);
    }

    static void setupChar(Creature* &c, int index)
    {
        switch(index)
        {
        case 0:
            c = new Doge();
            break;
        case 1:
            c = new Tiger();
            break;
        case 2:
            c = new Batman();
            break;
        case 3:
            c = new Sun();
            break;
        case 4:
            c = new Tornado();
            break;
        }
    }

    static void setupBar(Fightscene *fightscene)
    {
        fightscene->ui->playerHP->setText(QString::asprintf("%d/%d", fightscene->player->getHp(), fightscene->player->getMaxHp()));
        fightscene->ui->playerMP->setText(QString::asprintf("%d/%d", fightscene->player->getMp(), fightscene->player->getMaxMp()));
        fightscene->ui->rivalHP->setText(QString::asprintf("%d/%d", fightscene->rival->getHp(), fightscene->rival->getMaxHp()));
        fightscene->ui->playerHealthBar->setMaximum(fightscene->player->getMaxHp());
        fightscene->ui->playerHealthBar->setValue(fightscene->player->getHp());
        fightscene->ui->playerMagicBar->setMaximum(fightscene->player->getMaxMp());
        fightscene->ui->playerMagicBar->setValue(fightscene->player->getMp());
        fightscene->ui->rivalHealthBar->setMaximum(fightscene->rival->getMaxHp());
        fightscene->ui->rivalHealthBar->setValue(fightscene->rival->getHp());
    }

    static void setupSkillList(Fightscene *fightscene, list<Skill*> &skillList)
    {
        fightscene->ui->skillList->clear();
        for (list<Skill*>::iterator it = skillList.begin(); it != skillList.end(); ++it) {
            Skill* skill = *it;
            fightscene->ui->skillList->addItem("技能");
            fightscene->skillNameList.push_back("");
            fightscene->skillDescList.push_back(skill->getDescription());
        }
    }


    static QSequentialAnimationGroup* setShiftEffect(QLabel* label)
    {
        //设置不透明度属性
        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(label);
        opacityEffect->setOpacity(1);
        label->setGraphicsEffect(opacityEffect);

        //移入动画
        QPropertyAnimation *posAnimation_in = new QPropertyAnimation(label, "pos");
        posAnimation_in->setDuration(300);
        posAnimation_in->setStartValue(QPoint(200, 160));
        posAnimation_in->setEndValue(QPoint(320, 160));

        //淡入动画
        QPropertyAnimation  *opacityAnimation_in = new QPropertyAnimation(opacityEffect, "opacity");
        opacityAnimation_in->setDuration(300);
        opacityAnimation_in->setStartValue(0);
        opacityAnimation_in->setEndValue(1);

        //淡入动画组
        QParallelAnimationGroup *fadeInGroup = new QParallelAnimationGroup(label);
        fadeInGroup->addAnimation(posAnimation_in);
        fadeInGroup->addAnimation(opacityAnimation_in);

        //移动动画
        QPropertyAnimation *posAnimation = new QPropertyAnimation(label, "pos");
        posAnimation->setDuration(800);
        posAnimation->setStartValue(QPoint(320, 160));
        posAnimation->setEndValue(QPoint(380, 160));

        //移出动画
        QPropertyAnimation *posAnimation_out = new QPropertyAnimation(label, "pos");
        posAnimation_out->setDuration(300);
        posAnimation_out->setStartValue(QPoint(380, 160));
        posAnimation_out->setEndValue(QPoint(500, 160));

        //淡出动画
        QPropertyAnimation  *opacityAnimation_out = new QPropertyAnimation(opacityEffect, "opacity");
        opacityAnimation_out->setDuration(300);
        opacityAnimation_out->setStartValue(1);
        opacityAnimation_out->setEndValue(0);

        //淡出动画组
        QParallelAnimationGroup *fadeOutGroup = new QParallelAnimationGroup(label);
        fadeOutGroup->addAnimation(posAnimation_out);
        fadeOutGroup->addAnimation(opacityAnimation_out);

        //位移动画组
        QSequentialAnimationGroup *shiftGroup = new QSequentialAnimationGroup(label);
        shiftGroup->addAnimation(fadeInGroup);
        shiftGroup->addAnimation(posAnimation);
        shiftGroup->addAnimation(fadeOutGroup);

        return shiftGroup;
    }

    static QSequentialAnimationGroup* setCharEffect(QLabel* label)
    {
        //设置不透明度属性
        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(label);
        opacityEffect->setOpacity(1);
        label->setGraphicsEffect(opacityEffect);

        //淡入动画
        QPropertyAnimation  *opacityAnimation_in = new QPropertyAnimation(opacityEffect, "opacity");
        opacityAnimation_in->setDuration(500);
        opacityAnimation_in->setStartValue(0);
        opacityAnimation_in->setEndValue(1);

        //淡出动画
        QPropertyAnimation  *opacityAnimation_out = new QPropertyAnimation(opacityEffect, "opacity");
        opacityAnimation_out->setDuration(500);
        opacityAnimation_out->setStartValue(1);
        opacityAnimation_out->setEndValue(0);

        //淡入淡出动画组
        QSequentialAnimationGroup *fadeGroup = new QSequentialAnimationGroup(label);
        fadeGroup->addAnimation(opacityAnimation_in);
        fadeGroup->addAnimation(opacityAnimation_out);

        return fadeGroup;
    }

    static SkillType skillType[];
    static int skillTypeLen;

    static BuffType buffType[];
    static int buffTypeLen;

    static Buff* buffFactory(BuffType buffType, int effectVal, int round);
    static Skill* skillFactory(SkillType skillType, Creature* owner, int mpConsume, int effectVal, BuffType buffType, int round);
    static void getRandomSkill(Creature* owner);
};

template<class T>
T random(T a, T b) {
    return (rand() % (b - a + 1)) + a;
}

#endif // UTIL_H
