#include <QApplication>
//#include <QtConcurrentRun>

#include "mainwindow.h"
#include "threaddao.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    return a.exec();
}
