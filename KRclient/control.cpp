#include "control.h"
#include "common.h"
control::control(int n, QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Сontrol");
    layout=new QGridLayout;
    vlayout= new QVBoxLayout;
    number_call=new QPushButton*[n];
    number_sub=new QLineEdit*[n];
    sub=new QLabel*[n];
    out_sub=new QLabel*[n];
    output=new QLabel*[n];
    text_sub=new QTextEdit*[n];
    btn_compl=new QPushButton*[n];
    btn_acpt=new QPushButton*[n];
    btn_reject=new QPushButton*[n];
    QString s;
    for(int i=0;i<n;i++)
    {
        s="Абонент №";
        s+=QString().setNum(i+1);
        number_call[i]=new QPushButton("Вызвать");
        number_sub[i]=new QLineEdit("Номер вызываемого абонента");
        sub[i]=new QLabel(s);
        output[i]=new QLabel();
        layout->addWidget(number_call[i], 1, i);
        layout->addWidget(number_sub[i], 2, i);
        layout->addWidget(sub[i], 0, i);
        layout->addWidget(output[i], 5, i);
        connect(number_call[i], SIGNAL(pressed()), this, SLOT(callRequest()));
    }
    vlayout->addLayout(layout);
    vlayout->addStretch();
    setLayout(vlayout);    
}
control::~control()
{
    delete sub;
    delete number_call;
    delete number_sub;
    delete btn_acpt;
    delete btn_reject;
    delete btn_compl;
    delete text_sub;
    delete out_sub;
    delete output;
    delete layout;
    delete vlayout;
}
void control::callRequest()
{
    QPushButton *btn=(QPushButton*)sender();
    QString msg;
    for(int i=0;i<15;i++)
    {
        if (btn==number_call[i])
        {
            msg<<QString().setNum(i+1);
            msg<<QString().setNum(CALL_REQUEST);
            msg<<number_sub[i]->text();
        }
    }
    emit request(msg);
}
void control::answer(QString msg)
{
    QString text;
    int p = msg.indexOf(separator);
    int r = msg.left(p).toInt();
    msg=msg.right(msg.length()-p-1);
    p = msg.indexOf(separator);
        switch (r) {
        case (CALL_ANSWER):
            {
            int sub=msg.left(p).toInt();
            msg=msg.right(msg.length()-p-1);
            p = msg.indexOf(separator);
            int answ=msg.toInt();
            for (int i=0; i<15;i++)
            {
                output[i]->setText("");
                if (i+1==answ)
                {
                    btn_acpt[i]=new QPushButton("Снять трубку");
                    btn_reject[i]=new QPushButton("Отклонить вызов");
                    connect(btn_acpt[i], SIGNAL(pressed()), this, SLOT(acceptRequest()));
                    connect(btn_reject[i], SIGNAL(pressed()), this, SLOT(rejectRequest()));
                    layout->addWidget(btn_acpt[i], 3, i);
                    layout->addWidget(btn_reject[i], 4, i);
                    break;
                }
            }
            if(answ==16) output[sub-1]->setText("Достигнуто максимальное количество соединений");
            else if(answ==17) output[sub-1]->setText("Не задан номер у абонента");
            else if (answ==18) output[sub-1]->setText("Нельзя позвонить самому себе");
            else if(answ==19) output[sub-1]->setText("Не правильно набран номер");
            else if(answ==20) output[sub-1]->setText("Абонент занят");
            break;
            }
          case ACCEPT_ANSWER:
            {
                int sub1=msg.left(p).toInt();
                msg=msg.right(msg.length()-p-1);
                p = msg.indexOf(separator);
                int sub2=msg.left(p).toInt();
                for (int i=0;i<15;i++)
                {
                    output[i]->setText("");
                    if (i+1==sub1)
                    {
                        out_sub[i]=new QLabel();
                        text_sub[i]=new QTextEdit;
                        btn_compl[i]=new QPushButton("Завершить");
                        connect(btn_compl[i], SIGNAL(pressed()), this, SLOT(completeRequest()));
                        layout->addWidget(btn_compl[i], 3,i);
                        layout->addWidget(text_sub[i], 6, i);
                        layout->addWidget(out_sub[i], 7, i);
                        connect(text_sub[i], SIGNAL(textChanged()), this, SLOT(textRequest()));
                    }
                    if (i+1==sub2)
                    {
                        layout->removeWidget(btn_acpt[i]);
                        layout->removeWidget(btn_reject[i]);
                        delete btn_acpt[i];
                        delete btn_reject[i];
                        out_sub[i]=new QLabel();
                        text_sub[i]=new QTextEdit();
                        btn_compl[i]=new QPushButton("Завершить");
                        connect(btn_compl[i], SIGNAL(pressed()), this, SLOT(completeRequest()));
                        layout->addWidget(btn_compl[i], 3, i);
                        layout->addWidget(text_sub[i], 6, i);
                        layout->addWidget(out_sub[i], 7, i);
                        connect(text_sub[i], SIGNAL(textChanged()), this, SLOT(textRequest()));
                    }
                }
                layout->update();
                break;
         }
            case COMPLETE_ANSWER:
                {
                    p = msg.indexOf(separator);
                    int sub1=msg.left(p).toInt();
                    msg=msg.right(msg.length()-p-1);
                    p = msg.indexOf(separator);
                    int sub2=msg.left(p).toInt();
                    for (int i=0; i<15;i++)
                    {
                        output[i]->setText("");
                        if (i+1==sub1)
                        {
                            layout->removeWidget(text_sub[i]);
                            layout->removeWidget(btn_compl[i]);
                            layout->removeWidget(out_sub[i]);
                            delete btn_compl[i];
                            delete text_sub[i];
                            delete out_sub[i];
                        }
                        if (i+1==sub2)
                        {
                           layout->removeWidget(text_sub[i]);
                           layout->removeWidget(btn_compl[i]);
                           layout->removeWidget(out_sub[i]);
                           delete btn_compl[i];
                           delete text_sub[i];
                           delete out_sub[i];
                        }
                    }
                    layout->update();
                    break;
        }
        case REJECT_ANSWER:
            {
                p = msg.indexOf(separator);
                int sub1=msg.left(p).toInt();
                msg=msg.right(msg.length()-p-1);
                p = msg.indexOf(separator);
                int sub2=msg.left(p).toInt();
                for (int i=0; i<15;i++)
                {
                    output[i]->setText("");
                    if (i+1==sub2)
                    {
                        output[i]->setText("");
                        layout->removeWidget(btn_reject[i]);
                        layout->removeWidget(btn_acpt[i]);
                        delete btn_acpt[i];
                        delete btn_reject[i];
                    }
                }
                layout->update();
                break;
            }
        case TEXT_ANSWER:
            {
                int p = msg.indexOf(separator);
                int sub=msg.left(p).toInt();
                msg=msg.right(msg.length()-p-1);
                for (int i=0; i<15; i++)
                {
                    output[i]->setText("");
                    if (i+1==sub)
                    {
                        out_sub[i]->setText("");
                        if (msg.left(msg.length()-2)>30) layout->update();
                        out_sub[i]->setText(msg.left(msg.length()-2));
                    }
                }
                break;
        }
        default: return;
        }
}
void control::acceptRequest()
{
    QPushButton *btn=(QPushButton*)sender();
    QString msg;
    for (int i=0;i<15;i++)
    {
        if (btn==btn_acpt[i])
        {
            msg<<QString().setNum(i+1);
            msg<<QString().setNum(ACCEPT_REQUEST);
        }
    }
    emit request(msg);
}
void control::completeRequest()
{
    QPushButton *btn=(QPushButton*)sender();
    QString msg;
    for (int i=0; i<15;i++)
    {
        if (btn==btn_compl[i])
        {
            msg<<QString().setNum(i+1);
            msg<<QString().setNum(COMPLETE_REQUEST);
        }
    }
    emit request(msg);
}
void control::rejectRequest()
{
    QPushButton *btn=(QPushButton*)sender();
    QString msg;
    for (int i=0; i<15;i++)
    {
        if (btn==btn_reject[i])
        {
            msg<<QString().setNum(i+1);
            msg<<QString().setNum(REJECT_REQUEST);
        }
    }
    emit request(msg);
}
void control::textRequest()
{
    QTextEdit *text=(QTextEdit*)sender();
    QString msg;
    for (int i=0; i<15;i++)
    {
        if (text==text_sub[i])
        {
            msg<<QString().setNum(i+1);
            msg<<QString().setNum(TEXT_REQUEST);
            msg<<QString(text_sub[i]->toPlainText());
            if (text_sub[i]->toPlainText().length()>30) text_sub[i]->clear();
        }
    }
    emit request(msg);
}
