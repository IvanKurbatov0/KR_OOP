#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include "ats.h"
#include "communicator.h"
#include "subscriber.h"

class Application : public QCoreApplication
{
    Q_OBJECT

    TCommunicator *comm;
public:
    friend QByteArray& operator>>(QByteArray&, double&);
    friend QString& operator<<(QString&, double);
    Application(int, char**);
signals:

public slots:
    void recieve(QByteArray);

};

#endif // APPLICATION_H
