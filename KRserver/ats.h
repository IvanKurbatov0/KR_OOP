#ifndef ATS_H
#define ATS_H
#include "subscriber.h"
#include "line.h"
#include "QString"
class ATS
{
    int number_subscribers;
    int max_connect;
    int number_connect;
    Subscriber *subs;
public:
    ATS(const ATS& a);
    ATS& operator=(const ATS& a);
    ~ATS();
    Line *lines;
    ATS(int,int);
    int num(QString, int);
    int call(QString, int);
    int accept(int);
    int complete(int);
    int reject(int);
    int talk(int);
    int get_numbers_connect();
};

#endif // ATS_H
