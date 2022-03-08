#include "skill.h"
#include "Util.h"

void BuffSkill::act(Creature* owner, Creature* target) {
    Buff* buff = Util::buffFactory(buffType, effectVal, round);
    if (effectVal > 0) {
        owner->addBuff(buff);
    }
    else {
        target->addBuff(buff);
    }
}

QString BuffSkill::getName() {
    QString name;
    switch (buffType) {
    case BuffType::ATK: if(effectVal >= 0) name = "狂暴"; else name = "血脉抑制"; break;
    case BuffType::DEF: if (effectVal >= 0) name = "守护之盾"; else name = "破镜之刃"; break;
    case BuffType::MATK: if (effectVal >= 0) name = "法力无边"; else name = "源泉枯竭"; break;
    case BuffType::MDEF: if (effectVal >= 0) name = "光之盾"; else name = "灵魂逆流"; break;
    case BuffType::AGI: if (effectVal >= 0) name = "神速力"; else name = "沉重脚链"; break;
    case BuffType::ANTI_POISON: if (effectVal >= 0) name = "抗毒血清"; else name = "病村之露"; break;
    case BuffType::ANTI_CURSE: if (effectVal >= 0) name = "阳光普照"; else name = "黑暗童话"; break;
    case BuffType::POISON_HURT: name = "毒雾"; break;
    case BuffType::CURSE_HURT: name = "咒怨"; break;
    default: name = "失传之术";
    }
    return name;
}

QString BuffSkill::getDescription() {
    QString desc;

    int effect = effectVal;
    if (effect > 0) desc.append(" 己方 ");
    else desc.append(" 敌方 ");

    switch (buffType) {
        case BuffType::ATK: desc.append("攻击力"); break;
        case BuffType::DEF: desc.append("防御力") ; break;
        case BuffType::MATK: desc.append("魔法攻击力"); break;
        case BuffType::MDEF: desc.append("魔法防御力"); break;
        case BuffType::AGI: desc.append("敏捷"); break;
        case BuffType::ANTI_POISON: desc.append("毒抗性"); break;
        case BuffType::ANTI_CURSE: desc.append("诅咒抗性"); break;
        case BuffType::POISON_HURT: desc.append("中毒"); effect = std::max(effect, -effect); break;
        case BuffType::CURSE_HURT: desc.append("诅咒");  effect = std::max(effect, -effect); break;
    }

    desc.append(QString::asprintf(" %d, 持续回合：%d, mp消耗：%d", effect, round, mpConsume));
    return desc;
}

void MutiAtkSkill::act(Creature* owner, Creature* target) {
    int count = random<int>(1, 3);
    for (int i = 0; i < count; i++) {
        owner->attack();
    }
}

QString MutiAtkSkill::getName() {
    return "多刃剑";
}

QString MutiAtkSkill::getDescription() {
    return QString::asprintf("对敌方发起多次物理攻击，攻击力：%d, mp消耗：%d", effectVal, mpConsume);
}
