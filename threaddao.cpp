#include <QDebug>
#include <QEventLoop>
#include <QApplication>
#include <QPushButton>

#include "threaddao.h"
#include "sleeperthread.h"

const int SleepTimeMs = 10;
const int TooLong = 100;

ThreadDAO::ThreadDAO(QProgressIndicator &progressIndicator, QObject *parent) :
    QThread(parent),
    m_haveFunction(false),
    m_callFinished(false),
    m_stop(false),
    m_progressindicator(progressIndicator)
{
}


void ThreadDAO::run()
{
    qDebug() << "ThreadDAO::run";
    while (!m_stop)
    {
        while (!m_haveFunction)
        {
            SleeperThread::msSleep(SleepTimeMs);
        }
        m_callFinished = false;

        m_lambda();

        m_haveFunction = false;
        m_callFinished = true;
    }
}

void ThreadDAO::callSync(func lambda, QPushButton& btn)
{
    setLambda(lambda);

    bool animationIsShowed = false;
    int waitCycles = 0;

    while (m_haveFunction && !m_callFinished) {
        qApp->processEvents( QEventLoop::AllEvents );
        SleeperThread::msSleep(SleepTimeMs);
        ++waitCycles;
        if (waitCycles > TooLong && !animationIsShowed)
        {
            qDebug() << "Start animation";
            btn.setEnabled(false);
            m_progressindicator.startAnimation();
            animationIsShowed = true;
        }
    }

    if (animationIsShowed)
    {
        qDebug() << "Stop animation";
        btn.setEnabled(true);
        m_progressindicator.stopAnimation();
    }
}

void ThreadDAO::stopThread()
{
    qDebug() << "Stopping thread";
    m_stop = true;
}

void ThreadDAO::setLambda(func lambda)
{
    m_lambda = lambda;
    m_haveFunction = true;
    m_callFinished = false;
}
