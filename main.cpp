#include <iostream>
#include <QApplication>
#include "selectscene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Selectscene selectscene;
    selectscene.show();
    return a.exec();
}
