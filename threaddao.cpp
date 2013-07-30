#include <QDebug>

#include "threaddao.h"
#include "sleeperthread.h"

ThreadDAO::ThreadDAO(QObject *parent) :
    QThread(parent),
    haveFunction(false),
    callFinished(false),
    stop(false)
{
}

void ThreadDAO::run()
{
    qDebug() << "ThreadDAO::run";
    while (!stop)
    {
        while (!haveFunction)
        {
            SleeperThread::msSleep(10);
        }
        callFinished = false;

        m_lambda();

        haveFunction = false;
        callFinished = true;
    }
}

void ThreadDAO::stopThread()
{
    qDebug() << "Stopping thread";
    stop = true;
}

void ThreadDAO::setLambda(func lambda)
{
    m_lambda = lambda;
    haveFunction = true;
}
