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
#include <QThread>
bool stopThreads = false;
class TextThread : public QThread
{
public:
    TextThread( const QString &text );
    void run();
private:
    QString m_text;
};
TextThread::TextThread( const QString &text ) : QThread()
{
        m_text = text;
}
void TextThread::run()
{
    while( !stopThreads )
    {
        qDebug() << m_text;
        sleep( 1 );
    }
}

#include <QMutex>

const uint8_t philosophers = 5;
QMutex *tab = new QMutex[philosophers];
uint8_t iterations = 200;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMutex *tab = new QMutex[philosophers];

    // starving philosophers



    cout << "\nEveryting is okay\n";


    delete [] tab;

    return 0;
}
