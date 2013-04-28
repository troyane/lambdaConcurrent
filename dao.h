#ifndef DAO_H
#define DAO_H

#include <QObject>

// type lambda function
typedef std::function <void ()> func;


class DAO : public QObject
{
    Q_OBJECT
    QString mQuery;
public:
    DAO(QObject *parent = 0);

    void applyQuery(QString query, func freeze, func unfreeze);
};

#endif // DAO_H
