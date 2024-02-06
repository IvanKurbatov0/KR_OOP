#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
class control : public QWidget
{
    Q_OBJECT
public:
    explicit control(int, QWidget *parent = nullptr);
    QLabel **sub;
    QPushButton **number_call;
    QLineEdit **number_sub;
    QVBoxLayout *vlayout;
    QPushButton **btn_acpt;
    QPushButton **btn_reject;
    QPushButton **btn_compl;
    QGridLayout *layout;
    QTextEdit **text_sub;
    QLabel **out_sub;
    QLabel **output;
    ~control();
public slots:
    void rejectRequest();
    void callRequest();
    void acceptRequest();
    void completeRequest();
    void answer(QString);
    void textRequest();
signals:
    void request(QString);
};

#endif
