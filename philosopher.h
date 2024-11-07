#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <QThread>

class Philosopher : public QThread
{
public:
    explicit Philosopher(const uint8_t phNumber, QObject *parent = nullptr);

protected:
    void run() override;

private:
    uint8_t phNumber_;
};

#endif // PHILOSOPHER_H
