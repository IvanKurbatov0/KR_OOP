#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>

#include "mainwindow.h"
#include "communicator.h"
#include "state.h"
#include "common.h"

class Application : public QApplication
{
    Q_OBJECT

    TCommunicator *comm;
    mainWindow    *mainwin;

public:
    Application(int, char**);

public slots:
    void fromCommunicator(QByteArray);
    void toCommunicator(QString);

};

#endif // APPLICATION_H
