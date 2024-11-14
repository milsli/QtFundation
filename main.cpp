#include <QApplication>
#include <QDebug>
#include "mainwindow.h"


#include <QMutex>
#include "philosopher.h"
#include <QVector>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QObject parent;

    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
