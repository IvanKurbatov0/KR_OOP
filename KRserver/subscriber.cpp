#include "subscriber.h"
Subscriber::Subscriber()
{
    number="";
    index=0;
    status=READY;
}
Subscriber::Subscriber(int n)
{
    number="";
    index=n;
    status=READY;
}
int Subscriber::set_num(QString num)
{
    for (int i=0;i<len_number;i++)
    {
        if (!(num[i]>=48 && num[i]<=57)) return 1;
    }
    this->number.clear();
    this->number=num;
    return 0;
}
void Subscriber::set_status(int s)
{
    if (s>=0 && s<=2) status=s;
}
int Subscriber::get_status()
{
    return this->status;
}
QString Subscriber::get_num()
{
    return this->number;
}
int Subscriber::get_index()
{
    return this->index;
}
void Subscriber::set_index(int ind)
{
    index=ind;
}
