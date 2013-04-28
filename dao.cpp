#include <QFuture>
#include <QtConcurrentRun>
#include <QApplication>

#include "dao.h"
#include "sleeperthread.h"

// limit time when do we need to show message (in ms)
const unsigned long int LONG_OPERATION_TIME = 2000;

DAO::DAO(QObject *parent) :
    QObject(parent)
{
}

void DAO::applyQuery(QString query, func freeze, func unfreeze)
{
    mQuery = query;
    func daoBlock = [this] ()
    {
        // here (in lambda) goes block originally placed
        // in concrete dao's query implementation
        qDebug() << " # in DAO. Got Query: " << this->mQuery;
        // imitate working for a 3 sec
        qDebug() << " |  working ...";
        SleeperThread::msSleep(3000);
    };

    // send lambda work (originally dao's block) to other thread
    QFuture<void> f = QtConcurrent::run( daoBlock );

    // control time of thread working every 50 ms
    unsigned long int time = 0;
    bool overtime = false;
    while (f.isRunning())
    {
        SleeperThread::msSleep(50);
        qApp->processEvents();
        time += 50;
        if (!overtime)
            if ( time > LONG_OPERATION_TIME)
            {
                // Inform user. Show some progress bar, etc. -- placed
                //  in lambda parameter but only once when overtimed first
                overtime = true;
                freeze();
            }
    }
    if (overtime)
    {
        // Inform user. Hide some progress bar, etc.
        unfreeze();
    }
}
