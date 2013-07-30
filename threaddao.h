#ifndef THREADDAO_H
#define THREADDAO_H

#include <QThread>
#include "dao.h"

class ThreadDAO : public QThread
{
    Q_OBJECT

    bool haveFunction;
    bool callFinished;
    bool stop;

    func m_lambda;
public:
    explicit ThreadDAO(QObject *parent = 0);
    void run();
    void stopThread();

    void setLambda(func lambda);
    
signals:
//    void done();
    
public slots:    
};

#endif // THREADDAO_H
