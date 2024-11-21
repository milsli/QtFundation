#include "philosopher.h"

#include <QMutex>
#include <QDebug>

#include <QException>
#include <random>

using namespace std;

extern QVector<JoinedData> controlTab;

random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> dist(3, 8);
uniform_int_distribution<int> thinking(2, 4);

Philosopher::Philosopher(const uint8_t philosophers, const uint8_t phNumber, int capacity, QObject *parent)
    : QThread{parent}
    , philosophers_{philosophers}
    , phNumber_{phNumber}
    , capacity_{capacity}
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
            emit updateState(phNumber_, controlTab[phNumber_].phState, capacity_);
        }
        controlTab[phNumber_].phMutex->lock();
        controlTab[phNumber_].locked = true;

        bool locked = controlTab[(phNumber_ + 1) % philosophers_].phMutex->tryLock();
        if(locked == true)
        {
            controlTab[(phNumber_ + 1) % philosophers_].locked = true;
            uint32_t eatingTime = dist(mt);

            controlTab[phNumber_].phState = PhState::EATING;
            emit updateState(phNumber_, controlTab[phNumber_].phState, capacity_);

            capacity_ -= (eatingTime);
            msleep(700 * eatingTime);

            controlTab[phNumber_].locked = false;
            controlTab[(phNumber_ + 1) % philosophers_].locked = false;
            controlTab[phNumber_].phMutex->unlock();
            controlTab[(phNumber_ + 1) % philosophers_].phMutex->unlock();

            qDebug() << "Filozof nr " << phNumber_  + 1 << " jadł przez " << eatingTime << " minuty";
        }
        else
        {
            controlTab[phNumber_].phState = PhState::THINKING;
            emit updateState(phNumber_, controlTab[phNumber_].phState, capacity_);

            controlTab[phNumber_].locked = false;
            controlTab[phNumber_].phMutex->unlock();

            sleep(thinking(mt));       // thinking
        }

        previousState_ = controlTab[phNumber_].phState;
    }
    controlTab[phNumber_].phState = PhState::FULL;
    emit updateState(phNumber_, controlTab[phNumber_].phState, capacity_ >= 0 ? capacity_ : 0);

    qDebug() << "\nFilozof nr " << phNumber_  + 1 << " najedzony\n";
}
