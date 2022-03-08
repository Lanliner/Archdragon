#include <QMouseEvent>
#include "skillcard.h"

SkillCard::SkillCard(Fightscene *fightscene, QListWidget* parent): QListWidgetItem(parent) ,scene(fightscene)
{

}

SkillCard::SkillCard(list<Skill*>::iterator it, Fightscene *fightscene, QListWidget* parent): QListWidgetItem(parent), it(it), scene(fightscene)
{

}

void SkillCard::enterEvent(QEvent *event)
{

}

void SkillCard::leaveEvent(QEvent *event)
{

}

void SkillCard::mouseClickEvent(QMouseEvent *event)
{

}
