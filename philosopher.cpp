#include "philosopher.h"

#include <QMutex>
#include <QDebug>

using namespace std;

extern QMutex *mutexTab;
extern uint8_t philosophers;

Philosopher::Philosopher(const uint8_t phNumber, QObject *parent)
    : QThread{parent}
    , phNumber_{phNumber}
    , capacity_{100}
{
    qDebug() << "Filozof nr " << phNumber_ << " constructed";
    srand(time(nullptr));
}

void Philosopher::run()
{
    qDebug() << "Filozof nr " << phNumber_ << " started";
    while(capacity_ > 0)
    {
        mutexTab[phNumber_].lock();
        bool locked = mutexTab[(phNumber_ + 1) % philosophers].tryLock();

        if(locked == true)
        {
            uint32_t rnd = (4 * rand())/(RAND_MAX + 1);
            uint8_t eating = rnd + 2;

            capacity_ -= (eating + 1);
            msleep(600 * eating);

            mutexTab[phNumber_].unlock();
            mutexTab[(phNumber_ + 1) % philosophers].unlock();

            qDebug() << "Filozof nr " << phNumber_ << " jadł przez " << eating << " minuty";
        }
        else
        {
            mutexTab[phNumber_].unlock();
            sleep(1);       // thinking
        }
    }
    qDebug() << "\nFilozof nr " << phNumber_ << " najedzony\n";
}
