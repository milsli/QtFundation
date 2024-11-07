#include "philosopher.h"

#include <QMutex>

extern QMutex *tab;
extern uint8_t iterations;

Philosopher::Philosopher(const uint8_t phNumber, QObject *parent)
    : QThread{parent}
    , phNumber_{phNumber}
{

}

void Philosopher::run()
{
    while(iterations > 0)
    {
        bool locked = tab[phNumber_].tryLock();
    }
}
