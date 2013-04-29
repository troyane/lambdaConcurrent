#include <QFuture>
#include <QtConcurrentRun>
#include <QApplication>

#include "dao.h"
#include "sleeperthread.h"
#include <QMessageBox>

// limit time when do we need to show message (in ms)
const unsigned long int LONG_OPERATION_TIME = 2000;

DAO::DAO(QObject *parent) :
    QObject(parent)
{
}

// EventFilter to block all user input
bool DAO::eventFilter(QObject *obj, QEvent *ev)
{
    // do not block message boxes
    if ( obj->isWidgetType() ) {
        const QWidget* w = qobject_cast<QWidget*>(obj);
        if ( w ) {
            if ( qobject_cast<QMessageBox*>(w->window()) ) {
                return false;
            }
        }
    }
    switch ( ev->type() ) {
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    case QEvent::Shortcut:
    case QEvent::ShortcutOverride:

    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:

    case QEvent::Enter:
    case QEvent::Leave:

    case QEvent::FocusIn:
    case QEvent::FocusOut:
    case QEvent::ApplicationActivate:
    case QEvent::ApplicationDeactivate:
    case QEvent::RequestSoftwareInputPanel:
    case QEvent::CloseSoftwareInputPanel:{
        ev->accept();
        return true;
        break;
    }

    case QEvent::Quit:
    case QEvent::Close: {
        ev->ignore();
        return true;
        break;
    }

    default:
        break;
    }
    return false;
}

void DAO::applyQuery(QString query, func freeze, func unfreeze)
{
    // own event filter to block user input
    // to avoid deadlocks
    qApp->installEventFilter(this);

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
        // QEventLoop::ExcludeUserInputEvents -- if we have no own event filter
        //  so all events Qt'll handle after this while
        qApp->processEvents(QEventLoop::AllEvents);
        time += 50;
        if (!overtime)
            if ( time > LONG_OPERATION_TIME)
            {
                // Inform user. Show some progress bar, etc. -- placed
                //  in lambda parameter but only once when overtimed first
                overtime = true;
                qApp->setOverrideCursor(QCursor(Qt::WaitCursor));
                freeze();
            }
    }
    if (overtime)
    {
        // Inform user. Hide some progress bar, etc.
        qApp->restoreOverrideCursor();
        unfreeze();
    }

    //
    qApp->removeEventFilter(this);
}
