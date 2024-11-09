// #include "mainwindow.h"
// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     MainWindow w;
//     w.show();
//     return a.exec();
// }

#include <QApplication>
#include <iostream>
#include <QDebug>

using namespace std;

// DOING THINGS IN PARALLEL
// Semaphores
// #include <QThread>
// bool stopThreads = false;
// class TextThread : public QThread
// {
// public:
//     TextThread( const QString &text );
//     void run();
// private:
//     QString m_text;
// };
// TextThread::TextThread( const QString &text ) : QThread()
// {
//         m_text = text;
// }
// void TextThread::run()
// {
//     while( !stopThreads )
//     {
//         qDebug() << m_text;
//         sleep( 1 );
//     }
// }

#include <QMutex>
#include "philosopher.h"
#include <QVector>

uint8_t philosophers = 10;
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
