#include "MainWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget iWidget;
    iWidget.show();

    return a.exec();
}
