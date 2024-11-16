#include "philosopher.h"

#include <QMutex>
#include <QDebug>

#include <QException>
#include <random>

using namespace std;

extern QVector<JoinedData> controlTab;


random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> dist(0, 4);

Philosopher::Philosopher(const uint8_t philosophers, const uint8_t phNumber, QObject *parent)
    : QThread{parent}
    , philosophers_{philosophers}
    , phNumber_{phNumber}
    , capacity_{40}
{
    qDebug() << "Filozof nr " << phNumber_ << " constructed";
}

void Philosopher::run()
{
    qDebug() << "Filozof nr " << phNumber_ << " started";
    while(capacity_ > 0)
    {

        if(controlTab[phNumber_].phState != PhState::WAITING)
        {
            controlTab[phNumber_].phState = PhState::WAITING;
            emit updateState(controlTab[phNumber_].phState, phNumber_);
        }
        controlTab[phNumber_].phMutex->lock();
        controlTab[phNumber_].locked = true;

        bool locked = controlTab[(phNumber_ + 1) % philosophers_].phMutex->tryLock();
        if(locked == true)
        {
            controlTab[(phNumber_ + 1) % philosophers_].locked = true;
            uint32_t rnd = dist(mt);
            uint8_t eating = rnd + 2;

            controlTab[phNumber_].phState = PhState::EATING;
            emit updateState(controlTab[phNumber_].phState, phNumber_);

            capacity_ -= (eating + 5);
            msleep(700 * eating);

            controlTab[phNumber_].locked = false;
            controlTab[(phNumber_ + 1) % philosophers_].locked = false;
            controlTab[phNumber_].phMutex->unlock();
            controlTab[(phNumber_ + 1) % philosophers_].phMutex->unlock();

            qDebug() << "Filozof nr " << phNumber_  + 1 << " jadł przez " << eating << " minuty";
        }
        else
        {
            controlTab[phNumber_].phState = PhState::THINKING;
            emit updateState(controlTab[phNumber_].phState, phNumber_);

            controlTab[phNumber_].locked = false;
            controlTab[phNumber_].phMutex->unlock();

            msleep(1200);       // thinking
        }

        previousState_ = controlTab[phNumber_].phState;
    }
    controlTab[phNumber_].phState = PhState::FULL;
    emit updateState(controlTab[phNumber_].phState, phNumber_);

    qDebug() << "\nFilozof nr " << phNumber_  + 1 << " najedzony\n";
}
