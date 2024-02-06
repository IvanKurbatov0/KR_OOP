#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "state.h"
#include "control.h"
class mainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = nullptr);
    QPushButton *state_btn;
    QPushButton *control_btn;
    state *state_window;
    control *control_window;
    ~mainWindow();
public slots:
    void open_window_state();
    void open_window_control();
};

#endif
