#ifndef LINE_H
#define LINE_H
#include "subscriber.h"

class Line
{

public:
    Subscriber sub[2];
    bool ready;;
    Line();
};

#endif
