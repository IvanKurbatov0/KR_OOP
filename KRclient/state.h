#ifndef STATE_H
#define STATE_H
#include "communicator.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
class state : public QWidget
{
    Q_OBJECT
public:
    state(int, QWidget *parent = nullptr);
    QLabel **number;
    QLabel *num_connect, *val_connect;
    QLabel *state_subscriber;
    QLabel **state_sub;
    QLineEdit **num_val;
    QPushButton **btn;
    QVBoxLayout *vlayout;
    QGridLayout *layout;
    QLabel *output;
    ~state();
public slots:
    void answer(QString);
private slots:
    void numRequest();
signals:
    void request(QString);
};

#endif // STATE_H
