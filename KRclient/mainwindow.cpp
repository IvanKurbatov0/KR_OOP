#include "mainwindow.h"

mainWindow::mainWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Main Window");
    setFixedSize(300, 200);

    QVBoxLayout *layout=new QVBoxLayout;
    state_window=new state(15);
    control_window=new control(15);
    state_btn=new QPushButton("Окно состояния", this);
    control_btn=new QPushButton("Окно управления", this);
    layout->addWidget(state_btn);
    layout->addWidget(control_btn);
    setLayout(layout);
    connect(state_btn, SIGNAL(pressed()), this, SLOT(open_window_state()));
    connect(control_btn, SIGNAL(pressed()), this, SLOT(open_window_control()));
}

mainWindow::~mainWindow()
{
    delete state_btn;
    delete control_btn;
    delete state_window;
    delete control_window;
}

void mainWindow::open_window_state()
{
    state_window->showMaximized();
    state_window->show();
}

void::mainWindow::open_window_control()
{
    control_window->showMaximized();
    control_window->show();
}
