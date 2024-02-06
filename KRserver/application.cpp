#include "application.h"
#include "common.h"
#include "line.h"
ATS ats(15 ,4);

QString& operator<<(QString & s, int a)
{
    s+=QString().setNum(a);
    return s;
}

Application::Application(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                         QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);
    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
}

void Application::recieve(QByteArray msg)
{
    QString answer;
    int pos = msg.indexOf(separator);
    int sub=msg.left(pos).toInt();
    msg=msg.right(msg.length()-pos-1);
    pos = msg.indexOf(separator);
    int r;
    r = msg.left(pos).toInt();
    pos = msg.indexOf(separator);
    msg=msg.right(msg.length()-pos-1);
    switch (r) {
        case NUM_REQUEST:
            {
                QString num=msg.left(msg.indexOf(separator));
                answer << QString().setNum(NUM_ANSWER);
                answer << ats.num(num ,sub);
                break;
            }
        case CALL_REQUEST:
            {
                int s;
                QString answer2;
                QString num=msg.left(msg.indexOf(separator));
                s=ats.call(num, sub);
                answer2<<QString().setNum(STATUS_ANSWER);
                answer<<QString().setNum(CALL_ANSWER);
                answer<<QString().setNum(sub);
                answer<<s;
                if (s>0 && s<16)
                {
                    for (int i=0; i<4; i++)
                    {
                        if (!ats.lines[i].ready && (ats.lines[i].sub[0].get_index()==s || ats.lines[i].sub[1].get_index()==s))
                        {
                            for (int j=0; j<2;j++)
                            {
                                answer2<<QString().setNum(ats.lines[i].sub[j].get_index());
                                answer2<<QString().setNum(ats.lines[i].sub[j].get_status());
                            }
                        }
                    }
                }
                comm->send(QByteArray().append(answer2));
                break;
            }
        case ACCEPT_REQUEST:
            {
                int s;
                QString answer2, answer3;
                answer<<QString().setNum(ACCEPT_ANSWER);
                answer2<<QString().setNum(NUMBER_CONNECT);
                answer3<<QString().setNum(STATUS_ANSWER);
                s=ats.accept(sub);
                if (s<5)
                {
                    answer<<QString().setNum(ats.lines[s].sub[0].get_index());
                    answer<<ats.lines[s].sub[1].get_index();
                    for(int i=0;i<2;i++)
                    {
                        answer3<<QString().setNum(ats.lines[s].sub[i].get_index());
                        answer3<<QString().setNum(ats.lines[s].sub[i].get_status());
                    }
                }
                answer2<<QString().setNum(ats.get_numbers_connect());
                comm->send(QByteArray().append(answer2));
                comm->send(QByteArray().append(answer3));
                break;
            }
        case COMPLETE_REQUEST:
            {
                QString answer2, answer3;
                answer<<QString().setNum(COMPLETE_ANSWER);
                answer2<<QString().setNum(NUMBER_CONNECT);
                answer3<<QString().setNum(STATUS_ANSWER);
                int s=ats.complete(sub);
                if (s>=0 && s<5)
                {
                    answer<<QString().setNum(ats.lines[s].sub[0].get_index());
                    answer<<QString().setNum(ats.lines[s].sub[1].get_index());
                    for(int i=0;i<2;i++)
                    {
                        answer3<<QString().setNum(ats.lines[s].sub[i].get_index());
                        answer3<<QString().setNum(ats.lines[s].sub[i].get_status());
                    }
                }
                answer2<<QString().setNum(ats.get_numbers_connect());
                comm->send(QByteArray().append(answer2));
                comm->send(QByteArray().append(answer3));
                break;
            }
        case REJECT_REQUEST:
            {
               QString answer2;
               answer<<QString().setNum(REJECT_ANSWER);
               answer2<<QString().setNum(STATUS_ANSWER);
               int s=ats.reject(sub);
               if(s>=0 && s<5)
               {
                   answer<<QString().setNum(ats.lines[s].sub[0].get_index());
                   answer<<QString().setNum(ats.lines[s].sub[1].get_index());
                   for (int i=0;i<2;i++)
                   {
                       answer2<<QString().setNum(ats.lines[s].sub[i].get_index());
                       answer2<<QString().setNum(ats.lines[s].sub[i].get_status());
                   }
               }
               comm->send(QByteArray().append(answer2));
               break;
            }
        case TEXT_REQUEST:
            {
                QString text;
                answer<<QString().setNum(TEXT_ANSWER);
                int s =ats.talk(sub);
                if(s>=0 && s<5)
                {
                    for (int i=0; i<4;i++)
                    {
                        if (ats.lines[s].sub[i].get_index()!=sub)
                        {
                            answer<<QString().setNum(ats.lines[s].sub[i].get_index());
                            break;
                        }
                    }
                }
                text+=msg;
                answer<<text;
            }
    }
    comm->send(QByteArray().append(answer));
}
