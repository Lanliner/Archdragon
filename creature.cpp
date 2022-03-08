#include <QTimer>
#include "Creature.h"
#include "buff.h"
#include "skill.h"
#include "Util.h"

Creature::Creature(const char* name, int hp, int mp, int atk, int def, int matk, int mdef, int mpConsume, int agi, int antiPoisen, int antiCurse)
    : name(name)
    , hp(hp)
    , mp(mp)
    , atk(atk)
    , def(def)
    , matk(matk)
    , mdef(mdef)
    , mpConsume(mpConsume)
    , agi(agi)
    , antiPoison(antiPoisen)
    , antiCurse(antiCurse)
    , pixmap(":/resource/placeholder.jpg")
{
    maxHp = hp;
    maxMp = mp;
    buffList =  list<Buff*>();
    skillList =  list<Skill*>();
}

void Creature::autoAct() {
    attack();
}

void Creature::attack() {
    scene->setEffect(1);
    scene->addInfo(QString::asprintf("%s 进行攻击", getName()));
    scene->playShiftGroup();
    QTimer::singleShot(1400, scene, [=](){
        if (2 * agi >= enemy->agi)
            enemy->hurted(atk);
        else
            scene->addInfo(QString::asprintf("%s 躲开了", enemy->getName()));
        checkEnd();
    });
}
void Creature::hurted(int atk) {
    int damage = std::max(0, atk - def);
    setHp(hp - damage);
    scene->addInfo(QString::asprintf("%s 受到 %d 伤害", getName(), damage));
    playHurtAnime();
    health->setText(QString::asprintf("%d/%d", hp, maxHp));
    healthBar->setValue(hp);
}

bool Creature::magicAttack(){
    if (mp - mpConsume < 0) {
        scene->addInfo(QString::asprintf("%s mp不足", getName()));
        return false;
    }

    setMp(mp - mpConsume);
    magic->setText(QString::asprintf("%d/%d", mp, maxMp));
    magicBar->setValue(mp);

    scene->setEffect(2);
    scene->addInfo(QString::asprintf("%s 进行魔法攻击", getName()));
    scene->playShiftGroup();
    QTimer::singleShot(1400, scene, [=](){
        if (2 * agi >= enemy->agi)
            enemy->magicHurted(matk);
        else
            scene->addInfo(QString::asprintf("%s 躲开了", enemy->getName()));
        checkEnd();
    });
    return true;
}
void Creature::magicHurted(int matk) {
    int damage = std::max(0, matk - mdef);
    setHp(hp - damage);
    scene->addInfo(QString::asprintf("%s 受到 %d 魔法伤害", getName(), damage));
    playHurtAnime();
    health->setText(QString::asprintf("%d/%d", hp, maxHp));
    healthBar->setValue(hp);
}

void Creature::defend(){
    addBuff(Util::buffFactory(BuffType::DEF, def, 2));
    addBuff(Util::buffFactory(BuffType::MDEF, mdef, 2));
    scene->addInfo(QString::asprintf("%s 采取防御姿态", getName()));
    playDefendAnime();
    QTimer::singleShot(600, scene, [=](){
        checkEnd();
    });
}
void Creature::dodge(){
    addBuff(Util::buffFactory(BuffType::AGI, agi, 2));
    scene->addInfo(QString::asprintf("%s 采取闪避姿态", getName()));
    playDodgeAnime();
    QTimer::singleShot(600, scene, [=](){
        checkEnd();
    });
}
void Creature::poisonHurted(int poison) {
    poison = std::max(poison, -poison);
    int damage = std::max(0, poison - antiPoison);
    setHp(hp - damage);
    scene->addInfo(QString::asprintf("%s 受到 %d 中毒伤害", getName(), damage));
    health->setText(QString::asprintf("%d/%d", hp, maxHp));
    healthBar->setValue(hp);
}
void Creature::curseHurted(int curse) {
    curse = std::max(curse, -curse);
    int damage = std::max(0, curse - antiCurse);
    setHp(hp - damage);
    scene->addInfo(QString::asprintf("%s 受到 %d 诅咒伤害", getName(), damage));
    health->setText(QString::asprintf("%d/%d", hp, maxHp));
    healthBar->setValue(hp);
}

void Creature::addBuff(Buff* buff) {
    buff->start(this);
    // buffList->inputRear(buff);
    buffList.push_back(buff);
}

void Creature::traverseBuff() {
    /*ListNode<Buff*>* node = buffList->getHead()->getNext();
    while (node != NULL) {
        if (node->getData()->getRound() == 0) {
            node->getData()->end(this);
            ListNode<Buff*>* temp = node;
            node = node->getNext();
            buffList->remove(temp);
        }
        else {
            node->getData()->rounding(this);
            node = node->getNext();
        }
    }*/
    for (list<Buff*>::iterator it = buffList.begin(); it != buffList.end();) {
        Buff* buff = *it;
        if (buff->getRound() == 0) {
            buff->end(this);
            it = buffList.erase(it);
        }
        else {
            buff->rounding(this);
            it++;
        }
    }
    if(hp == 0 || enemy->getHp() == 0) {
        QTimer::singleShot(500, scene, [=](){
            emit scene->gameOver();
        });
        return;
    }
}

//void Creature::showAllSkill() {
//    /*ListNode<Skill*>* node = skillList->getHead()->getNext();
//    int index = 0;
//    while (node != NULL) {
//        printf("[%d]\n", index);
//        node = node->getNext();
//        index++;
//    }*/
//    int index = 0;
//    for (list<Skill*>::iterator itor = skillList.begin(); itor != skillList.end(); ++itor) {
//        Skill* skill = *itor;
//        printf("[%d]", index);
//        skill->getDescription();
//        index++;
//    }
//}

void Creature::addSkill(Skill* skill) {
    // skillList->inputRear(skill);
    skillList.push_back(skill);
    scene->addSkill(skill);
    scene->addInfo(QString("获得了技能 ").append(skill->getName()));
}

//bool Creature::launchSkill(list<Skill*>::iterator it) {
//    Skill* skill = *it;
//    if (mp - skill->getMpConsume() < 0) {
//        scene->addInfo(QString::asprintf("%s mp不足\n", getName()));
//        return false;
//    }
//    skill->act(this, enemy);
//    setMp(mp - skill->getMpConsume());
//    skillList.erase(it);
//    return true;
//}

bool Creature::launchSkill(int index) {
    int count = 0;
    for (list<Skill*>::iterator it = skillList.begin(); it != skillList.end();) {
        Skill* skill = *it;
        if (index == count) {
            if (mp - skill->getMpConsume() < 0) {
                scene->addInfo(QString::asprintf("%s mp不足", getName()));
                return false;
            }
            playSkillAnime();
            skill->act(this, enemy);
            setMp(mp - skill->getMpConsume());
            magic->setText(QString::asprintf("%d/%d", mp, maxMp));
            magicBar->setValue(mp);
            scene->addInfo(QString::asprintf("%s 发动了 ", getName()).append(skill->getName()));
            QTimer::singleShot(800, scene, [=](){
                checkEnd();
            });
            it = skillList.erase(it);
            break;
        }
        else {
            it++;
            count++;
        }
    }
    return true;
}

void Creature::setScene(Fightscene* scene
                        , QLabel *effectLabel
                        , QLabel *charEffectLabel
                        , QProgressBar *healthBar
                        , QLabel *health
                        , QProgressBar *magicBar
                        , QLabel *magic)
{
    this->scene = scene;
    this->effectLabel = effectLabel;
    this->charEffectLabel = charEffectLabel;
    this->healthBar = healthBar;
    this->health = health;
    this->magicBar = magicBar;
    this->magic = magic;

    effectLabel->setPixmap(pixmap);
}

void Creature::tagPlayer()
{
    isPlayer = true;
}

void Creature::checkEnd()
{
    if(enemy->getHp() == 0) {
        QTimer::singleShot(300, scene, [=](){
            emit scene->gameOver();
        });
        return;
    }
    QTimer::singleShot(1000, scene, [=](){
        if(isPlayer)
            emit scene->playerEnd();
        else
            emit scene->rivalEnd();
    });
}

void Creature::playSkillAnime()
{
    charEffectLabel->setPixmap(QPixmap(":/resource/halo.png"));
    if(isPlayer) {
        scene->playPlayerEffectGroup();
    }
    else {
        scene->playRivalEffectGroup();
    }
}

void Creature::playDefendAnime()
{
    charEffectLabel->setPixmap(QPixmap(":/resource/shield.png"));
    if(isPlayer) {
        scene->playPlayerEffectGroup();
    }
    else {
        scene->playRivalEffectGroup();
    }
}

void Creature::playDodgeAnime()
{
    charEffectLabel->setPixmap(QPixmap(":/resource/run.png"));
    if(isPlayer) {
        scene->playPlayerEffectGroup();
    }
    else {
        scene->playRivalEffectGroup();
    }
}

void Creature::playHurtAnime()
{
    int x = effectLabel->geometry().x();
    int y = effectLabel->geometry().y();
    effectLabel->move(x - 10, y - 10);
    QTimer::singleShot(50, effectLabel, [=](){
        effectLabel->move(x - 10, y + 5);
    });
    QTimer::singleShot(100, effectLabel, [=](){
        effectLabel->move(x, y);
    });
}

//Creature(const char* name,
//      int hp, int mp, int atk, int def, int matk,
//      int mdef,int mpConsume, int agi, int antiPoison, int antiCurse);

Batman::Batman(): Creature("百特曼", 150, 100, 45, 25, 40, 20, 20, 30, 10, 10)
{
    pixmap.load(":/resource/char_batman.jpg");
    prologue = "\"我面具下是谁不重要，但是我的所作所为会解释这一切。\"";
}

Doge::Doge(): Creature("刀哥", 80, 160, 42, 30, 44, 20, 20, 44, 20, 20)
{
    pixmap.load(":/resource/char_doge.jpg");
    prologue = "\"来沈阳大街，指定没你好果汁吃嗷。\"";
}

Tiger::Tiger(): Creature("虎哥", 100, 60, 60, 30, 30, 20, 10, 35, 15, 10)
{
    pixmap.load(":/resource/char_tiger.jpg");
    prologue = "\"OK兄弟们，全体目光向我看齐！\"";
}

Tornado::Tornado(): Creature("龙卷风", 200, 50, 40, 40, 30, 8, 10, 28, 5, 1)
{
    pixmap.load(":/resource/char_tornado.jpg");
    prologue = "\"哼！想逃？闪电旋风劈！\"";
}

Sun::Sun(): Creature("孙哥", 140, 120, 42, 30, 36, 16, 16, 30, 1, 30)
{
    pixmap.load(":/resource/char_sun.jpg");
    prologue = "\"其实我是一个非常儒雅随和的一个人。\"";
}




