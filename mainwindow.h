#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "types.h"

class Philosopher;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void setupMenu();

    void paintPhilosopher(const int nr, QPainter &painter, const int yPos, const PhState state, int angle);
    void paintPhilosophers(QPainter &painter, const int yPos);
    void paintTable(QPainter &painter, const int yPos);
    void paintPlate(QPainter &painter, const int x, const int y);
    void paintStick(QPainter &painter, const int x, const int y);
    void paintStikcs(QPainter &painter, const int x, const int y);

    void drawGrid(QPainter &painter);

private slots:
    void setupSimulation();
    void startSimulation(const int phNumber);
    void updateDraw(int nr, PhState st, int16_t capacity);

private:
    int phNumber_;
    int plateSize_;
    int startCapacity_;
    QVector<int> capacityTab_;

};

#endif // MAINWINDOW_H
