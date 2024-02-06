#include "ats.h"
ATS::ATS(int number_subs,int number_lines)
{
    number_subscribers=number_subs;
    number_connect=0;
    subs=new Subscriber[number_subscribers];
    for(int i=0; i<number_subs;i++)
    {
        subs[i].set_index(i+1);
    }
    lines=new Line[number_lines];
    for(int i=0; i<number_lines; i++)
    {
        lines[i].ready=true;
    }
    max_connect=number_lines;
}
ATS::ATS(const ATS& a)
{
    if (this!=&a)
    {
        number_subscribers=a.number_subscribers;
        number_connect=a.number_connect;
        max_connect=a.max_connect;
        subs=new Subscriber[number_subscribers];
        for(int i=0; i<number_subscribers;i++)
        {
            subs[i]=a.subs[i];
        }
        lines=new Line[max_connect];
        for(int i=0; i<max_connect;i++)
        {
            lines[i]=a.lines[i];
        }
    }
}
ATS::~ATS()
{
    delete[] subs;
    delete[] lines;
}
ATS& ATS::operator=(const ATS& a)
{
    if (this!=&a)
    {
        this->~ATS();
        number_subscribers=a.number_subscribers;
        number_connect=a.number_connect;
        max_connect=a.max_connect;
        subs=new Subscriber[number_subscribers];
        for(int i=0; i<number_subscribers;i++)
        {
            subs[i]=a.subs[i];
        }
        lines=new Line[max_connect];
        for(int i=0; i<max_connect;i++)
        {
            lines[i]=a.lines[i];
        }
        return *this;
    }
}
int ATS::num(QString num, int index_sub)
{
    if (num.length()==len_number)
    {
        for(int i=0;i<number_subscribers;i++)
        {
            if (subs[i].get_num()==num) return 1;
        }
        for(int i=0;i<number_subscribers;i++)
        {
            if (index_sub==subs[i].get_index())
            {
                if (subs[i].set_num(num)==0)
                {
                    return 0;
                }
                else return 2;
            }
            else continue;
        }
    }
    return 2;
}
int ATS::call(QString num, int index_sub)
{
   if (number_connect>=max_connect) return 16;
   if (subs[index_sub-1].get_num()=="") return 17;
   bool flag=false;
   int index_sub2=0;
   for(int i=0;i<number_subscribers;i++)
   {
       if(subs[i].get_num()==num)
       {
           flag=1;
           index_sub2=subs[i].get_index();
       }
   }
   if (flag)
   {
       if (subs[index_sub2-1].get_status()!=READY) return 20;
       if(index_sub==index_sub2) return 18;
       for(int j=0; j<max_connect;j++)
       {
           if (lines[j].ready)
           {
               for(int i=0;i<number_subscribers;i++)
               {
                   if(subs[i].get_index()==index_sub)
                   {
                       subs[i].set_status(CALL);
                       lines[j].sub[0]=subs[i];
                   }
                   else if (subs[i].get_index()==index_sub2)
                   {
                       subs[i].set_status(CALL);
                       lines[j].sub[1]=subs[i];
                   }
               }
               lines[j].ready=false;
               return index_sub2;
           }
       }
   }
   return 19;
}
int ATS::accept(int sub)
{
    for (int j=0;j<max_connect;j++)
    {
        if ((lines[j].sub[0].get_index()==sub)|| (lines[j].sub[1].get_index()==sub))
        {
            for (int i=0; i<number_subscribers;i++)
            {
                for (int k=0; k<2;k++)
                {
                    if(subs[i].get_index()==lines[j].sub[k].get_index())
                    {
                        subs[i].set_status(TALK);
                        lines[j].sub[k]=subs[i];
                    }
                }
            }
            lines[j].ready=false;
            number_connect++;
            return j;
        }
        else continue;
    }
    return 2;
}
int ATS::complete(int sub)
{
    for(int j=0; j<max_connect;j++)
    {
        if (!lines[j].ready)
        {
            if (lines[j].sub[0].get_index()==sub || lines[j].sub[1].get_index()==sub)
            {
                lines[j].ready=true;
                for(int i=0; i<number_subscribers;i++)
                {
                    for(int k=0; k<2;k++)
                    {
                        if (subs[i].get_index()==lines[j].sub[k].get_index())
                        {
                            subs[i].set_status(READY);
                            lines[j].sub[k]=subs[i];
                        }
                    }
                }
                number_connect--;
                return j;
            }
        }
        else continue;
    }
    return 5;
}
int ATS::reject(int sub)
{
    for(int j=0; j<max_connect;j++)
    {
        if (!lines[j].ready && (lines[j].sub[0].get_index()==sub || lines[j].sub[1].get_index()==sub))
        {
            for(int i=0; i<number_subscribers;i++)
            {
                for(int k=0; k<2;k++)
                {
                    if (subs[i].get_index()==lines[j].sub[k].get_index())
                    {
                        subs[i].set_status(READY);
                        lines[j].sub[k]=subs[i];
                    }
                }
            }
            lines[j].ready=true;
            return j;
        }
        else continue;
    }
    return 5;
}
int ATS::talk(int sub)
{
    for(int j=0; j<max_connect;j++)
    {
        if (!lines[j].ready && (lines[j].sub[0].get_index()==sub || lines[j].sub[1].get_index()==sub))
        {
            return j;
        }
    }
    return 5;
}
int ATS::get_numbers_connect()
{
    return number_connect;
}
