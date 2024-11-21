#include "mainwindow.h"

#include <QMenuBar>
#include "setupsimulationdialog.h"

#include <QDebug>
#include "philosopher.h"
#include <QRect>

QVector<JoinedData> controlTab;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    , phNumber_{0}
    , plateSize_{30}
    , startCapacity_{200}
{
    setGeometry(10, 30, 1800, 950);
    setupMenu();
}

MainWindow::~MainWindow()
{    
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
    setupAction_ = new QAction("Setup");
    startAction_ = new QAction("Start");
    QMenu *simulationMenu = new QMenu("Simulation", this);

    simulationMenu->addAction(setupAction_);
    simulationMenu->addAction(startAction_);
    startAction_->setDisabled(true);

    QMenuBar *menuBar = new QMenuBar(this);
    menuBar->addMenu(simulationMenu);
    setMenuBar(menuBar);

    connect(setupAction_, &QAction::triggered, this, &MainWindow::setupSimulation);
    connect(startAction_, &QAction::triggered, this, &MainWindow::startSimulation);
}

void MainWindow::startSimulation()
{
    startAction_->setDisabled(true);
    for(uint8_t i = 0; i < phNumber_; ++i)
    {
        controlTab[i].philosopher->start();
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
    painter.drawText(x, y, QString::number(nr + 1));

    painter.drawEllipse({x, y}, headSize / 2, headSize / 2);

    QRect torso(x - (headSize), y + headSize / 2 + 2, headSize * 2, headSize * 2);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;
    painter.drawChord(torso, startAngle, spanAngle);
    painter.drawText(x - 8, y + headSize, QString::number(capacityTab_[nr]));

    paintPlate(painter, x, y);

    painter.save();

    if(controlTab[nr].phState == PhState::EATING)
    {
        painter.rotate(-angle / 4);
        paintStick(painter, x, y - 90);
    }
    else if(controlTab[nr > 0 ? nr - 1 : (phNumber_ - 1)].phState == PhState::EATING)
    {
        painter.rotate(-3 * (angle / 4));
        paintStick(painter, x, y - 90);
    }
    else
    {
        painter.rotate(-angle / 2);
        paintStick(painter, x, y);
    }

    painter.restore();
}

void MainWindow::paintPhilosophers(QPainter &painter, const int yPos)
{
   //  QMutexLocker locker(&paintingMutex);
    painter.save();
    int angle = 360 / phNumber_;

    for(int i = 0; i < phNumber_; ++i)
    {
        paintPhilosopher(i, painter, yPos, controlTab[i].phState, angle);
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

        controlTab.resize(phNumber_);
        capacityTab_.resize(phNumber_);
        int counter = 0;
        for(JoinedData & d: controlTab)
        {
            Philosopher *ph = new Philosopher(phNumber_, counter, startCapacity_ , this);
            d.philosopher = ph;
            connect(d.philosopher, SIGNAL(updateState(int, PhState, int16_t)), this, SLOT(updateDraw(int, PhState, int16_t)));

            d.phMutex = new QMutex;
            d.phState = PhState::WAITING;

            capacityTab_[counter] = startCapacity_;

            ++counter;
        }
        update();
        startAction_->setEnabled(true);
        setupAction_->setEnabled(false);
    }
}

void MainWindow::updateDraw(int nr, PhState st, int16_t capacity)
{
    QString state = "EATING";
    if(st == PhState::FULL)
    {
        state = "FULL";
        controlTab[nr].philosopher->wait();
        delete controlTab[nr].philosopher;

        if(!setupAction_->isEnabled())
            setupAction_->setEnabled(true);

    }
    else if(st == PhState::THINKING)
        state = "THINKING";
    else if(st == PhState::WAITING)
        state = "WAITING";

    capacityTab_[nr] = capacity;
    update();
}
