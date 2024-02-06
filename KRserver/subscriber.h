#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include <QString>
#define READY 0
#define TALK 1
#define CALL 2
#define len_number 10
class Subscriber
{
    QString number;
    int status;
    int index;
public:
    Subscriber();
    Subscriber(int);
    int set_num(QString);
    QString get_num();
    void set_status(int);
    int get_status();
    int get_index();
    void set_index(int);
};

#endif // SUBSCRIBER_H
