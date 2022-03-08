#include "buff.h"

// AtkBuff
void AtkBuff::start(Creature* c) {
    c->setAtk(c->getAtk() + effectVal);
    AtkBuff::rounding(c);
}
void AtkBuff::rounding(Creature* c) {
    if (effectVal > 0) c->getScene()->addInfo(QString::asprintf("%s 提升攻击力...", c->getName()));
    else c->getScene()->addInfo(QString::asprintf("%s 降低攻击力...", c->getName()));
    round--;
}
void AtkBuff::end(Creature* c) {
    c->setAtk(c->getAtk() - effectVal);
}

// DefBuff
void DefBuff::start(Creature* c) {
    c->setDef(c->getDef() + effectVal);
    DefBuff::rounding(c);
}
void DefBuff::rounding(Creature* c) {
    if (effectVal > 0)c->getScene()->addInfo(QString::asprintf("%s 提升防御力...", c->getName()));
    else c->getScene()->addInfo(QString::asprintf("%s 降低防御力...", c->getName()));
    round--;
}
void DefBuff::end(Creature* c) {
    c->setDef(c->getDef() - effectVal);
}

// MatkBuff
void MatkBuff::start(Creature* c) {
    c->setMatk(c->getMatk() + effectVal);
    MatkBuff::rounding(c);
}
void MatkBuff::rounding(Creature* c) {
    if (effectVal > 0) c->getScene()->addInfo(QString::asprintf("%s 提升魔法攻击力...", c->getName()));
    else c->getScene()->addInfo(QString::asprintf("%s 降低魔法攻击力...", c->getName()));
    round--;
}
void MatkBuff::end(Creature* c) {
    c->setMatk(c->getMatk() - effectVal);
}

// MdefBuff
void MdefBuff::start(Creature* c) {
    c->setMdef(c->getMdef() + effectVal);
    MdefBuff::rounding(c);
}
void MdefBuff::rounding(Creature* c) {
    if (effectVal > 0) c->getScene()->addInfo(QString::asprintf("%s 提升魔法防御力...", c->getName()));
    else c->getScene()->addInfo(QString::asprintf("%s 降低魔法防御力...", c->getName()));
    round--;
}
void MdefBuff::end(Creature* c) {
    c->setMdef(c->getMdef() - effectVal);
}

// AgiBuff
void AgiBuff::start(Creature* c) {
    c->setAgi(c->getAgi() + effectVal);
    AgiBuff::rounding(c);
}
void AgiBuff::rounding(Creature* c) {
    if (effectVal > 0) c->getScene()->addInfo(QString::asprintf("%s 提升敏捷...", c->getName()));
    else c->getScene()->addInfo(QString::asprintf("%s 降低敏捷...", c->getName()));
    round--;
}
void AgiBuff::end(Creature* c) {
    c->setAgi(c->getAgi() - effectVal);
}

// AntiPoisonBuff
void AntiPoisonBuff::start(Creature* c) {
    c->setAntiPoison(c->getAntiPoison() + effectVal);
    AntiPoisonBuff::rounding(c);
}
void AntiPoisonBuff::rounding(Creature* c) {
    if (effectVal > 0) c->getScene()->addInfo(QString::asprintf("%s 提升毒抗性...", c->getName()));
    else c->getScene()->addInfo(QString::asprintf("%s 降低毒抗性...", c->getName()));
    round--;
}
void AntiPoisonBuff::end(Creature* c) {
    c->setAntiPoison(c->getAntiPoison() - effectVal);
}

// AntiCurseBuff
void AntiCurseBuff::start(Creature* c) {
    c->setAntiCurse(c->getAntiCurse() + effectVal);
    round--;
}
void AntiCurseBuff::rounding(Creature* c) {
    if (effectVal > 0) c->getScene()->addInfo(QString::asprintf("%s 提升诅咒抗性...", c->getName()));
    else c->getScene()->addInfo(QString::asprintf("%s 降低诅咒抗性...", c->getName()));
    round--;
}
void AntiCurseBuff::end(Creature* c) {
    c->setAntiCurse(c->getAntiCurse() - effectVal);
}

// PoisonHurtBuff
void PoisonHurtBuff::start(Creature* c) {
    c->getScene()->addInfo(QString::asprintf("%s 中毒了！...", c->getName()));
}
void PoisonHurtBuff::rounding(Creature* c) {
    c->getScene()->addInfo(QString::asprintf("%s 中毒...", c->getName()));
    c->poisonHurted(effectVal);
    round--;
}
void PoisonHurtBuff::end(Creature* c) {
    c->getScene()->addInfo(QString::asprintf("%s 中毒解除...", c->getName()));
}

// CurseHurtBuff
void CurseHurtBuff::start(Creature* c) {
    c->getScene()->addInfo(QString::asprintf("%s 被诅咒了！...", c->getName()));
}
void CurseHurtBuff::rounding(Creature* c) {
    c->getScene()->addInfo(QString::asprintf("%s 受到诅咒...", c->getName()));
    c->curseHurted(effectVal);
    round--;
}
void CurseHurtBuff::end(Creature* c) {
    c->getScene()->addInfo(QString::asprintf("%s 诅咒解除...", c->getName()));
}
