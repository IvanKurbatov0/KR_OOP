#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    NUM_REQUEST = 1,
    CALL_REQUEST,
    NUM_ANSWER,
    CALL_ANSWER,
    ACCEPT_REQUEST,
    ACCEPT_ANSWER,
    REJECT_REQUEST,
    COMPLETE_REQUEST,
    COMPLETE_ANSWER,
    NUMBER_CONNECT,
    STATUS_ANSWER,
    REJECT_ANSWER,
    TEXT_REQUEST,
    TEXT_ANSWER,
};

extern const QChar separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H
