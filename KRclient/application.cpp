#include "application.h"

Application::Application(int argc, char *argv[])
            : QApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10001,
                         QHostAddress("127.0.0.1"), 10000};
    comm = new TCommunicator(pars, this);
    mainwin = new mainWindow();
    mainwin->show();
    connect(comm,SIGNAL(recieved(QByteArray)),this,
            SLOT(fromCommunicator(QByteArray)));
    connect(mainwin->state_window,SIGNAL(request(QString)),
           this,SLOT(toCommunicator(QString)));
    connect(mainwin->control_window,SIGNAL(request(QString)),
           this,SLOT(toCommunicator(QString)));
}

void Application::fromCommunicator(QByteArray msg)
{
    int p = msg.indexOf(separator);
    if (msg.left(p).toInt()==NUM_ANSWER || msg.left(p).toInt()==NUMBER_CONNECT || msg.left(p).toInt()==STATUS_ANSWER) mainwin->state_window->answer(QString(msg));
    else if(msg.left(p).toInt()==CALL_ANSWER || msg.left(p).toInt()==ACCEPT_ANSWER || msg.left(p).toInt()==COMPLETE_ANSWER || msg.left(p).toInt()==REJECT_ANSWER || msg.left(p).toInt()==TEXT_ANSWER) mainwin->control_window->answer(QString(msg));
}

void Application::toCommunicator(QString msg)
{
    comm->send(QByteArray().append(msg));
}
