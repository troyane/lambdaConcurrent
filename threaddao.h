#ifndef THREADDAO_H
#define THREADDAO_H

#include <QThread>
#include "dao.h"
#include "QProgressIndicator.h"

class ThreadDAO : public QThread
{
    Q_OBJECT

    bool m_haveFunction;
    bool m_callFinished;
    bool m_stop;

    func m_lambda;
    QProgressIndicator& m_progressindicator;
public:
    explicit ThreadDAO(QProgressIndicator& progressIndicator, QObject *parent = 0);
    void run();
    void callSync(func lambda);
    void stopThread();

    void setLambda(func lambda);

    
signals:
//    void done();
    
public slots:    
};

#endif // THREADDAO_H
