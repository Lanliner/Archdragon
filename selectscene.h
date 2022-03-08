#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include <QWidget>

namespace Ui { class Selectscene; }

class Selectscene : public QWidget
{
    Q_OBJECT
public:
    Selectscene(QWidget *parent = nullptr);
    ~Selectscene();

private:
    friend class Util;
    Ui::Selectscene *ui;
};

#endif // SELECTSCENE_H
