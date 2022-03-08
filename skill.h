#ifndef SKILL_H
#define SKILL_H

#include "creature.h"
#include "buff.h"

class Util;

enum class SkillType {
	BUFF = 0, MUTI_ATK
};

class Skill {
protected:
	Creature* owner;
	int effectVal;
	int mpConsume;
public:
	Skill(Creature* owner, int mpConsume, int effectVal = 10) :owner(owner), mpConsume(mpConsume), effectVal(effectVal){}
	virtual void act(Creature* owner, Creature* target) = 0;
    virtual QString getName() = 0;
    virtual QString getDescription() = 0;
	int getMpConsume() { return mpConsume; }
};

class BuffSkill : public Skill {
protected:
	BuffType buffType;
	int round;
public:
	BuffSkill(Creature* owner, int mpConsume, int effectVal, BuffType buffType, int round = 2)
		:buffType(buffType), round(round), Skill(owner, mpConsume, effectVal) { }
	virtual void act(Creature* owner, Creature* target);
    QString getName();
    QString getDescription();
};

class MutiAtkSkill : public Skill {
public:
	MutiAtkSkill(Creature* owner, int mpConsume) : Skill(owner, mpConsume) {}
	virtual void act(Creature* owner, Creature* target);
    QString getName();
    QString getDescription();
};

#endif //SKILL_H
