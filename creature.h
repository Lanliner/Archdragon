#ifndef CREATURE_H
#define CREATURE_H

#include <QString>
#include <QWidget>

#include <iostream>
#include <list>
#include <QLabel>
#include <QProgressBar>
#include "fightscene.h"

using std::string;
using std::list;
class Skill;
class Buff;
class Fightscene;

class Creature
{
public:
    QPixmap pixmap;

    friend class Fightscene;

    Creature(const char* name, int hp, int mp, int atk, int def, int matk, int mdef, int mpConsume, int agi, int antiPoison, int antiCurse);
    //~Creature();
    virtual void autoAct();
    virtual void attack();
    virtual void hurted(int atk);
    virtual bool magicAttack();
    virtual void magicHurted(int matk);
    virtual void defend();
    virtual void dodge();
    virtual void poisonHurted(int poison);
    virtual void curseHurted(int curse);

    void addBuff(Buff* buff);
    void traverseBuff();
    void showAllSkill();
    void addSkill(Skill* skill);
    bool launchSkill(list<Skill*>::iterator it);
    bool launchSkill(int index);

    const char* getName() { return name; }

    int getHp() { return hp; }
    int getMaxHp() { return maxHp; }
    int getMp() { return mp; }
    int getMaxMp() { return maxMp; }
    int getAtk() { return atk; }
    int getDef() { return def; }
    int getMatk() { return matk; }
    int getMdef() { return mdef; }
    int getAgi() { return agi; }
    int getAntiPoison() { return antiPoison; }
    int getAntiCurse() { return antiCurse; }
    QProgressBar* getHealthBar() { return healthBar; }
    QLabel* getHealth() { return health; }
    Fightscene* getScene() { return scene; }
    QString getPrologue() { return prologue; }

    void setHp(int hp) { this->hp = std::max(0, hp); }
    void setMp(int mp) { this->mp = std::max(0, mp); }
    void setAtk(int atk) { this->atk = std::max(1, atk); }
    void setDef(int def) { this->def = std::max(1, def); }
    void setMatk(int matk) { this->matk = std::max(1, matk); }
    void setMdef(int mdef) { this->mdef = std::max(1, mdef); }
    void setAgi(int agi) { this->agi = std::max(1, agi); }
    void setAntiPoison(int antiPoisen) { this->antiPoison = std::max(1, antiPoisen); }
    void setAntiCurse(int antiCurse) { this->antiCurse = std::max(1, antiCurse); }

    void setEnemy(Creature* enemy) { this->enemy = enemy; }

    void setScene(Fightscene* scene, QLabel *effectLabel, QLabel *charEffectLabel, QProgressBar *healthBar
                  , QLabel *health, QProgressBar *magicBar = nullptr, QLabel *magic = nullptr);

    void tagPlayer();
    void checkEnd();

    //动画
    void playSkillAnime();
    void playDefendAnime();
    void playDodgeAnime();
    void playHurtAnime();

protected:
    const char* name;
    int maxHp;
    int maxMp;

    int hp;
    int mp;
    int atk;
    int def;
    int matk;
    int mdef;
    int mpConsume;
    int agi;
    int antiPoison;
    int antiCurse;

    bool isPlayer = false; //玩家标记
    QString prologue; //开场白

    Creature* enemy;
    // LinkedList<Buff*>* buffList;
    // LinkedList<Skill*>* skillList;
    list<Buff*> buffList;
    list<Skill*> skillList;

    //界面属性
    Fightscene *scene;
    QLabel *effectLabel;
    QLabel *charEffectLabel;
    QProgressBar *healthBar;
    QLabel *health;
    QProgressBar *magicBar;
    QLabel *magic;
};

class Batman : public Creature
{
public:
    Batman();
};

class Doge : public Creature
{
public:
    Doge();
};

class Tiger : public Creature
{
public:
    Tiger();
};

class Tornado : public Creature
{
public:
    Tornado();
};

class Sun : public Creature
{
public:
    Sun();
};

#endif // CREATURE_H
