#include "widget.h"
#include "ui_widget.h"
#include <auto_form.h>
#include <control_form.h>
#include <monitor_form.h>
#include <info_form.h>
#include <qtimer.h>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setGeometry(0,0,800,480);
    this->setStyleSheet("background-color: rgba(196, 255, 242, 100%);");
    ui->closebtn->setStyleSheet("QPushButton{qproperty-icon:url(/home/icdyeing/four_stepping/icon/close.png)}");
    connect(sub,SIGNAL(sub_start()),sub,SLOT(sub_cmd()));

}

Widget::~Widget()
{
    sub->sub_cmd_break();
    sub_thread.quit();
    delete ui;
}

// DELAY
void Widget::delay_msec(unsigned int msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec,&loop,SLOT(quit()));
    loop.exec();
}

// SIGNAL
void Widget::on_auto_btn_clicked()
{
    auto_form *autoform = new auto_form();
    this->close();
    autoform->show();
}

void Widget::on_monitor_btn_clicked()
{
    monitor_form *monitorform = new monitor_form();
    this->close();
    monitorform->show();
}

void Widget::on_contorl_btn_clicked()
{
    control_form *controlform = new control_form();
    this->close();
    controlform->show();
}

void Widget::on_info_btn_clicked()
{
    info_form *infoform = new info_form();
    this->close();
    infoform->show();
}

void Widget::on_closebtn_clicked()
{
    this->close();
    delete this;
}

void sub_sub::sub_cmd()
{
    iscanrun = true;
    sub_out = false;
    int a=0;
    while(1)
    {
        {
            QMutexLocker locker(&lock);
            if(!iscanrun)
            {
                sub_out = true;
                break;
            }
        }
        system("/home/icdyeing/mqtt/1sub_cmd.sh");
        a++;
        qDebug()<<"1sub_cmd.sh "<<a<<" times"<<endl;
        //Widget::delay_msec(1500);
        QThread::msleep(50);
    }

}

void sub_sub::sub_cmd_break()
{

    QMutexLocker locker(&lock);
    iscanrun = false;

    qDebug()<<"sub_cmd_break"<<endl;
}
