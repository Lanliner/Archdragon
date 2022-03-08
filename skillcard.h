#ifndef SKILLCARD_H
#define SKILLCARD_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include "fightscene.h"
#include "skill.h"

using namespace std;

class SkillCard : public QListWidgetItem
{
    Q_OBJECT
public:
    SkillCard(Fightscene *fightscene);
    SkillCard(list<Skill*>::iterator it, Fightscene *fightscene, QListWidget* parent = nullptr);

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mouseClickEvent(QMouseEvent *event);

private:
    list<Skill*>::iterator it;
    Fightscene *scene;
};

#endif // SKILLCARD_H
