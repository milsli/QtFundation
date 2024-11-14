#include "philosopher.h"

#include <QMutex>
#include <QDebug>

#include <QException>

using namespace std;

extern QVector<JoinedData> controlTab;
//extern QMutex *mutexTab;

QMutex releaseMutex;
extern QVector<PhState> statesVector;

Philosopher::Philosopher(const uint8_t philosophers, const uint8_t phNumber, QObject *parent)
    : QThread{parent}
    , philosophers_{philosophers}
    , phNumber_{phNumber}
    , capacity_{60}
{
    qDebug() << "Filozof nr " << phNumber_ << " constructed";
}

void Philosopher::run()
{
    qDebug() << "Filozof nr " << phNumber_ << " started";
    while(capacity_ > 0)
    {

        if(statesVector[phNumber_] != PhState::WAITING)
        {
            statesVector[phNumber_] = PhState::WAITING;
            emit updateState(statesVector[phNumber_], phNumber_);
        }
        controlTab[phNumber_].phMutex->lock();
        controlTab[phNumber_].locked = true;
        // mutexTab[phNumber_].lock();

//        bool locked = mutexTab[(phNumber_ + 1) % philosophers_].tryLock();
        bool locked = controlTab[(phNumber_ + 1) % philosophers_].phMutex->tryLock();

        if(locked == true)
        {
            controlTab[(phNumber_ + 1) % philosophers_].locked = true;
            uint32_t rnd = (4 * rand())/(RAND_MAX + 1);
            uint8_t eating = rnd + 2;

            statesVector[phNumber_] = PhState::EATING;
            emit updateState(statesVector[phNumber_], phNumber_);

            capacity_ -= (eating + 5);
            msleep(700 * eating);

            //    QMutexLocker locl(&releaseMutex);
                // mutexTab[phNumber_].unlock();
                // mutexTab[(phNumber_ + 1) % philosophers_].unlock();

            controlTab[phNumber_].locked = false;
            controlTab[(phNumber_ + 1) % philosophers_].locked = false;
            controlTab[phNumber_].phMutex->unlock();
            controlTab[(phNumber_ + 1) % philosophers_].phMutex->unlock();

            qDebug() << "Filozof nr " << phNumber_  + 1 << " jadł przez " << eating << " minuty";
        }
        else
        {
            statesVector[phNumber_] = PhState::THINKING;
            emit updateState(statesVector[phNumber_], phNumber_);
            //mutexTab[phNumber_].unlock();

            controlTab[phNumber_].locked = false;
            controlTab[phNumber_].phMutex->unlock();

            msleep(1200);       // thinking
        }

        previousState_ = statesVector[phNumber_];
    }
    statesVector[phNumber_] = PhState::FULL;
    emit updateState(statesVector[phNumber_], phNumber_);

    qDebug() << "\nFilozof nr " << phNumber_  + 1 << " najedzony\n";
}
