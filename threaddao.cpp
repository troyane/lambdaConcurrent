#include <QDebug>
#include <QEventLoop>
#include <QApplication>

#include "threaddao.h"
#include "sleeperthread.h"

const int SleepTimeMs = 10;

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
        m_callFinished = false
                ;
        m_progressindicator.startAnimation();
        m_lambda();
        m_progressindicator.stopAnimation();

        m_haveFunction = false;
        m_callFinished = true;
    }
}

void ThreadDAO::callSync(func lambda)
{
    QEventLoop::ProcessEventsFlags processEventFlags = QEventLoop::AllEvents;
    setLambda(lambda);
    while (m_haveFunction && !m_callFinished) {
        qApp->processEvents( processEventFlags );
        SleeperThread::msSleep(SleepTimeMs);
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
