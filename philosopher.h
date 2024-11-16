#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <QThread>
#include "types.h"

class Philosopher : public QThread
{
    Q_OBJECT
public:
    explicit Philosopher(const uint8_t philosophers, const uint8_t phNumber, int capacity, QObject *parent = nullptr);
    // ~Philosopher(){wait();}

protected:
    void run() override;

signals:
    void updateState(int, PhState, int16_t);

private:
    uint8_t philosophers_;
    uint8_t phNumber_;
    int capacity_;
    PhState previousState_;
};

#endif // PHILOSOPHER_H
