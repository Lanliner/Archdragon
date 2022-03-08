#include "Util.h"

SkillType Util::skillType[] = { SkillType::BUFF, SkillType::MUTI_ATK };
int Util::skillTypeLen = sizeof(skillType) / sizeof(SkillType);

BuffType Util::buffType[] = { BuffType::ATK, BuffType::DEF, BuffType::MATK, BuffType::MDEF, BuffType::AGI, BuffType::ANTI_POISON,
		BuffType::ANTI_CURSE, BuffType::POISON_HURT, BuffType::CURSE_HURT };
int Util::buffTypeLen = sizeof(buffType) / sizeof(BuffType);

Buff* Util::buffFactory(BuffType buffType, int effectVal, int round) {
	Buff* buff = NULL;
	switch (buffType) {
		case BuffType::ATK: buff = new AtkBuff(effectVal, round); break;
		case BuffType::DEF: buff = new DefBuff(effectVal, round); break;
		case BuffType::MATK: buff = new MatkBuff(effectVal, round); break;
		case BuffType::MDEF: buff = new MdefBuff(effectVal, round); break;
		case BuffType::AGI: buff = new AgiBuff(effectVal, round); break;
		case BuffType::ANTI_POISON: buff = new AntiPoisonBuff(effectVal, round); break;
		case BuffType::ANTI_CURSE: buff = new AntiCurseBuff(effectVal, round); break;
		case BuffType::POISON_HURT: buff = new PoisonHurtBuff(std::max(effectVal, -effectVal), round); break;
		case BuffType::CURSE_HURT: buff = new CurseHurtBuff(std::max(effectVal, -effectVal), round); break;
		default: ATK: buff = new AtkBuff(effectVal, round); break;
	}
	return buff;
}

Skill* Util::skillFactory(SkillType skillType, Creature* owner, int mpConsume, int effectVal, BuffType buffType, int round) {
	Skill* skill = NULL;
	switch (skillType) {
	case SkillType::BUFF: skill = new BuffSkill(owner, mpConsume, effectVal, buffType, round); break;
	case SkillType::MUTI_ATK: skill = new MutiAtkSkill(owner, mpConsume); break;
	default: MUTI_ATK: skill = new MutiAtkSkill(owner, mpConsume); break;
	}
	return skill;
}

void Util::getRandomSkill(Creature* owner) {
    int skillIndex = random<int>(0, skillTypeLen - 1);
    int mpConsume = random<int>(0, 30);
   int effectVal = random<int>(-30, 30);
    int buffIndex = random<int>(0, buffTypeLen - 1);
    int round = random<int>(2, 4);
    Skill* skill = Util::skillFactory(skillType[0], owner, mpConsume, effectVal, buffType[buffIndex], round);
	owner->addSkill(skill);
}
