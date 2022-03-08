#ifndef BUFF_H
#define BUFF_H
#include <iostream>
#include "creature.h"
using std::string;

enum class BuffType {
    ATK= 0, DEF, MATK, MDEF, AGI, ANTI_POISON, ANTI_CURSE, POISON_HURT, CURSE_HURT
};

class Buff {
protected:
    int effectVal;	// 正值表示buff，负值表示debuff
    int round;
public:
    Buff(int effectVal, int round) : effectVal(effectVal), round(std::max(1, round)) { }
    virtual void start(Creature* c) = 0;
    virtual void rounding(Creature* c) = 0;
    virtual void end(Creature* c) = 0;

    int getRound() { return round; }
};

/* 增加攻击力或降低攻击力*/
class AtkBuff: public Buff {
public:
    AtkBuff(int effectVal, int round): Buff(effectVal, round) { }
    virtual void start(Creature* c);
    virtual void rounding(Creature* c);
    virtual void end(Creature* c);
};

/* 增加防御力或降低防御力*/
class DefBuff : public Buff {
public:
    DefBuff(int effectVal, int round) : Buff(effectVal, round) { }
    virtual void start(Creature* c);
    virtual void rounding(Creature* c);
    virtual void end(Creature* c);
};

/* 增加魔法攻击力或降低魔法攻击力*/
class MatkBuff : public Buff {
public:
    MatkBuff(int effectVal, int round) : Buff(effectVal, round) { }
    virtual void start(Creature* c);
    virtual void rounding(Creature* c);
    virtual void end(Creature* c);
};

/* 增加魔法防御力或降低魔法防御力*/
class MdefBuff : public Buff {
public:
    MdefBuff(int effectVal, int round) : Buff(effectVal, round) { }
    virtual void start(Creature* c);
    virtual void rounding(Creature* c);
    virtual void end(Creature* c);
};

/* 增加敏捷或降低敏捷*/
class AgiBuff : public Buff {
public:
    AgiBuff(int effectVal, int round) : Buff(effectVal, round) { }
    virtual void start(Creature* c);
    virtual void rounding(Creature* c);
    virtual void end(Creature* c);
};

/* 增加毒耐性或降低毒耐性*/
class AntiPoisonBuff : public Buff {
public:
    AntiPoisonBuff(int effectVal, int round) : Buff(effectVal, round) { }
    virtual void start(Creature* c);
    virtual void rounding(Creature* c);
    virtual void end(Creature* c);
};

/* 增加诅咒耐性或降低诅咒耐性*/
class AntiCurseBuff : public Buff {
public:
    AntiCurseBuff(int effectVal, int round) : Buff(effectVal, round) { }
    virtual void start(Creature* c);
    virtual void rounding(Creature* c);
    virtual void end(Creature* c);
};

/* 中毒*/
class PoisonHurtBuff : public Buff {
public:
    PoisonHurtBuff(int effectVal, int round) : Buff(effectVal, round) { }
    virtual void start(Creature* c);
    virtual void rounding(Creature* c);
    virtual void end(Creature* c);
};


/* 被诅咒*/
class CurseHurtBuff : public Buff {
public:
    CurseHurtBuff(int effectVal, int round) : Buff(effectVal,  round) { }
    virtual void start(Creature* c);
    virtual void rounding(Creature* c);
    virtual void end(Creature* c);
};

#endif //BUFF_H
