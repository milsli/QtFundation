#ifndef TYPES_H
#define TYPES_H

#include <QMutex>

class Philosopher;

enum class PhState
{
    EATING,
    WAITING,
    THINKING,
    FULL
};

typedef struct central
{
    QMutex *phMutex;
    Philosopher *philosopher;
    bool locked = false;
    PhState phState;
} JoinedData;

#endif // TYPES_H
