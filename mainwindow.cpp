#include "mainwindow.h"

#include <QMenuBar>
#include "setupsimulationdialog.h"

#include <QDebug>
#include "philosopher.h"
#include <QRect>

QVector<JoinedData> controlTab;
//QMutex *mutexTab;

QMutex paintingMutex;
QVector<PhState> statesVector;



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    , phNumber_{0}
    , plateSize_{30}
{
    statesVector.resize(phNumber_);
    setGeometry(10, 30, 1800, 950);
    setupMenu();
}

MainWindow::~MainWindow()
{
    for(uint8_t i = 0; i < phNumber_; ++i)
    {
        philosopherTab_[i]->wait();
    }
    for(uint8_t i = 0; i < phNumber_; ++i)
    {
        delete philosopherTab_[i];
    }
    //delete [] mutexTab;

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(phNumber_ == 0)
        return;

    // drawGrid(painter);
    QSize range = size();
    painter.translate(range.width() / 2, range.height() / 2);
    int yPos = 3 * range.height() / 7;
    paintPhilosophers(painter, yPos);
    paintTable(painter, yPos);
}

void MainWindow::setupMenu()
{
    QAction *setupAction = new QAction("Setup");
    QAction *startAction = new QAction("Start");
    QMenu *simulationMenu = new QMenu("Simulation", this);

    simulationMenu->addAction(setupAction);
    simulationMenu->addAction(startAction);

    QMenuBar *menuBar = new QMenuBar(this);
    menuBar->addMenu(simulationMenu);
    setMenuBar(menuBar);

    connect(setupAction, &QAction::triggered, this, &MainWindow::setupSimulation);
    connect(startAction, &QAction::triggered, this, &MainWindow::startSimulation);
}

void MainWindow::startSimulation(const int phNumber)
{
    srand(time(nullptr));

    // mutexTab = new QMutex[phNumber_];

    qDebug() << "Mutex's tab constructed";
    philosopherTab_.resize(phNumber_);
    qDebug() << "Philosophers's tab constructed";

    for(uint8_t i = 0; i < phNumber_; ++i)
    {
        Philosopher *ph = new Philosopher(phNumber_, i, this);
        philosopherTab_[i] = ph;
        connect(philosopherTab_[i], SIGNAL(updateState(PhState, int)), this, SLOT(updateDraw(PhState, int)));
    }

    for(uint8_t i = 0; i < phNumber_; ++i)
    {
        philosopherTab_[i]->start();
    }

    qDebug() << "Everyting is created and started";
}

void MainWindow::paintPhilosopher(const int nr, QPainter &painter, const int yPos, const PhState state, int angle)
{
    QPen phPen(Qt::darkGreen);
    if(state == PhState::THINKING)
        phPen.setColor(Qt::darkRed);
    else if(state == PhState::FULL)
        phPen.setColor(Qt::black);
    else if(state == PhState::EATING)
        phPen.setColor(Qt::blue);

    phPen.setStyle(Qt::SolidLine);
    phPen.setWidth(4);
    painter.setPen(phPen);

    int x = 0;
    int y = -yPos;

    int headSize = 40;
    painter.drawText(x, y, QString::number(nr));

    painter.drawEllipse({x, y}, headSize / 2, headSize / 2);

    QRect torso(x - (headSize), y + headSize / 2 + 2, headSize * 2, headSize * 2);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;

    painter.drawChord(torso, startAngle, spanAngle);

    paintPlate(painter, x, y);

    painter.save();

    // painter.rotate(-angle / 2);
    // if(state == PhState::EATING)
    //     paintStick(painter, x, y - 90);
    // else
    //     paintStick(painter, x, y);

    painter.rotate(-angle / 2);
    if(controlTab[nr-1].locked == true)
        paintStick(painter, x, y - 90);
    else
        paintStick(painter, x, y);

    painter.restore();
}

void MainWindow::paintPhilosophers(QPainter &painter, const int yPos)
{
    QMutexLocker locker(&paintingMutex);
    painter.save();
    int angle = 360 / phNumber_;

    for(int i = 0; i < phNumber_; ++i)
    {
        paintPhilosopher(i + 1, painter, yPos, statesVector[i], angle);
        painter.rotate(angle);
    }

    painter.restore();
}

void MainWindow::paintTable(QPainter &painter, const int yPos)
{
    QPen tablePen(Qt::black);
    tablePen.setWidth(3);
    painter.setPen(tablePen);
    painter.drawEllipse( QPoint{0, 0}, yPos - 70, yPos - 70);
}

void MainWindow::paintPlate(QPainter &painter, const int x, const int y)
{
    QPen platePen(Qt::darkGray);
    platePen.setStyle(Qt::SolidLine);
    platePen.setWidth(9);

    QBrush oldBrush = painter.brush();
    QBrush plateBrush(Qt::gray);
    painter.setPen(platePen);
    painter.setBrush(plateBrush);

    plateSize_ = 30;
    painter.drawEllipse({x, y + 120}, plateSize_, plateSize_);

    painter.setBrush(oldBrush);
}

void MainWindow::paintStick(QPainter &painter, const int x, const int y)
{
    QPen stickPen(Qt::darkCyan);
    stickPen.setWidth(5);

    painter.setPen(stickPen);
    painter.drawLine(x, y + 90, x , y + 150);
}

void MainWindow::paintStikcs(QPainter &painter, const int x, const int y)
{
    QPen stickPen(Qt::darkCyan);
    stickPen.setWidth(3);

    painter.setPen(stickPen);

    painter.drawLine(x - (plateSize_ / 2) - 25, y + 90, x - (plateSize_ / 2) - 25, y + 150);
    painter.drawLine(x + (plateSize_ / 2) + 25, y + 90, x + (plateSize_ / 2) + 25, y + 150);
}

void MainWindow::drawGrid(QPainter &painter)
{
    QPen yellowPen(Qt::yellow);
    yellowPen.setStyle(Qt::SolidLine);
    painter.setPen(yellowPen);
    QSize mainWindowSize = size();

    for(int i = 0; i < mainWindowSize.width(); i += 200)
    {
        painter.drawLine(i, 0, i, mainWindowSize.height());
    }
    for(int i = 0; i < mainWindowSize.height(); i += 200)
    {
        painter.drawLine(0, i, mainWindowSize.width(), i);
    }
}

void MainWindow::setupSimulation()
{
    SetupSimulationDialog *dialog = new SetupSimulationDialog(this);
    if(dialog->exec() == QDialog::Accepted)
    {
        int phNumber = dialog->getPhNumber();        

        phNumber_ = phNumber;
        statesVector.resize(phNumber_);
        statesVector.fill(PhState::WAITING);

        controlTab.resize(phNumber_);
        for(JoinedData & d: controlTab)
        {
            d.phMutex = new QMutex;
        }

        update();
    }
}

void MainWindow::updateDraw(PhState st, int nr)
{
    QString state = "EATING";
    if(st == PhState::FULL)
        state = "FULL";
    else if(st == PhState::THINKING)
        state = "THINKING";
    else if(st == PhState::WAITING)
        state = "WAITING";

    qDebug() << "   updating " << nr + 1 <<" - " << state;
    update();
}
