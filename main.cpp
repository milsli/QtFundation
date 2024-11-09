#include <QApplication>
#include <QDebug>

using namespace std;

#include <QMutex>
#include "philosopher.h"
#include <QVector>

uint8_t philosophers = 8;
QMutex *mutexTab;
uint8_t iterations = 200;

int main(int argc, char *argv[])
{
    qDebug() << "Everyting is start to be constructed";

    QApplication a(argc, argv);
    QObject parent;

    qDebug() << "Everyting is start to be constructed";

    mutexTab = new QMutex[philosophers];
    qDebug() << "Mutex's tab constructed";
    QVector<Philosopher*> philosopherTab(philosophers);
    qDebug() << "Philosophers's tab constructed";

    for(uint8_t i = 0; i < philosophers; ++i)
    {
        Philosopher *ph = new Philosopher(i, &parent);
        philosopherTab[i] = ph;

        philosopherTab[i]->start();
    }

    qDebug() << "Everyting is created and started";

    for(uint8_t i = 0; i < philosophers; ++i)
    {
        philosopherTab[i]->wait();
    }

    qDebug() << "Everyting is completed";
    qDebug() << "Start to delete";

    for(uint8_t i = 0; i < philosophers; ++i)
    {
        delete philosopherTab[i];
    }

    delete [] mutexTab;

    qDebug() << "Everything is deleted";

    return 0;
}
