#include "state.h"
#include "common.h"
state::state(int sub, QWidget *parent) : QWidget(parent)
{
    setWindowTitle("State");
    vlayout=new QVBoxLayout;
    layout=new QGridLayout;

    number =new QLabel*[sub];
    state_sub=new QLabel*[sub];
    num_val=new QLineEdit*[sub];
    btn=new QPushButton*[sub];
    QString s;
    for (int i=0; i<sub;i++)
    {
        s="Номер абонент №";
        s+=QString().setNum(i+1);
        number[i]=new QLabel(s, this);
        state_sub[i]=new QLabel("Готов", this);
        num_val[i]=new QLineEdit("Номер", this);
        btn[i]=new QPushButton("Записать номер", this);
        layout->addWidget(number[i], i+1,0);
        layout->addWidget(state_sub[i], i+1, 3);
        layout->addWidget(num_val[i], i+1, 1);
        layout->addWidget(btn[i], i+1, 2);
        connect(btn[i], SIGNAL(pressed()), this, SLOT(numRequest()));
    }
    num_connect=new QLabel("Количество соединений:", this);
    state_subscriber=new QLabel("Состояние абонента", this);
    val_connect=new QLabel("0", this);
    output=new QLabel(this);
    layout->addWidget(val_connect, 16, 1);
    layout->addWidget(state_subscriber, 0, 3);
    layout->addWidget(num_connect, 16, 0);
    vlayout->addLayout(layout);
    vlayout->addWidget(output);
    vlayout->addStretch();
    setLayout(vlayout);
}
state::~state()
{
    delete number;
    delete num_connect;
    delete val_connect;
    delete state_subscriber;
    delete state_sub;
    delete num_val;
    delete btn;
    delete output;
    delete layout;
    delete vlayout;
}
void state::numRequest()
{
    QString msg;
    QPushButton *bt = (QPushButton*)sender();
    for (int i=0; i<15; i++)
    {
        if (bt==btn[i])
        {
            msg << QString().setNum(i+1);
            msg << QString().setNum(NUM_REQUEST);
            msg<<num_val[i]->text();
        }
    }

    emit request(msg);
}
void state::answer(QString msg)
{
    QString text;
    int p = msg.indexOf(separator);
    int r = msg.left(p).toInt();
    msg=msg.right(msg.length()-p-1);
    switch (r)
    {
        case NUM_ANSWER:
        if(msg.toInt()==2)
        {
            text += "Не правильно набран номер";
            output->setText(text);
        }
        else if (msg.toInt()==1)
            {
                text += "Данный номер уже существует";
                output->setText(text);
            }
        else if(msg.toInt()==0)
        {
            output->setText("Номер добавлен");
        }
            break;
        case NUMBER_CONNECT:
        {
            QString num_connect=msg.left(1);
            val_connect->setText(num_connect);
            break;
        }
        case STATUS_ANSWER:
        {
        int p = msg.indexOf(separator);

            int sub1=msg.left(p).toInt();
            msg=msg.right(msg.length()-p-1);
            p = msg.indexOf(separator);
            int s1=msg.left(p).toInt();
            msg=msg.right(msg.length()-p-1);
            p = msg.indexOf(separator);
            int sub2=msg.left(p).toInt();
            msg=msg.right(msg.length()-p-1);
            p = msg.indexOf(separator);
            int s2=msg.left(p).toInt();
            QString status1 ,status2;
            switch (s1)
            {
                case 0:
                    status1="Готов";
                break;
                case 1:
                    status1="Разговаривает";
                    break;
                case 2:
                status1="Вызов";
                break;
            default:return;
            }
            switch (s2)
            {
                case 0:
                    status2="Готов";
                break;
                case 1:
                    status2="Разговаривает";
                    break;
                case 2:
                    status2="Вызов";
                break;
            default:return;
            }
            for(int i=0;i<15;i++)
            {
              if (sub1 ==i+1)
              {
                  state_sub[i]->setText(status1);
              }
              if (sub2==i+1)
              {
                  state_sub[i]->setText(status2);
              }
            }
        }
    }
}
