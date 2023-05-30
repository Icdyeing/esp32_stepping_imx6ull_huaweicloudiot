#include "control_form.h"
#include "ui_control_form.h"
#include <widget.h>
#include <qthread.h>

control_form::control_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::control_form)
{
    ui->setupUi(this);
    this->setGeometry(0,0,800,480);
    this->setStyleSheet("background-color: rgba(196, 255, 242, 100%);");

    ui->btn_fifty_2->setEnabled(false);
    ui->btn_for_2->setEnabled(false);
    ui->btn_re_2->setEnabled(false);
    ui->btn_seventy_2->setEnabled(false);
    ui->btn_stop_2->setEnabled(false);
    ui->btn_twenty_2->setEnabled(false);
    ctl_button_check(dir,duty);
}

control_form::~control_form()
{
    delete ui;
}

// check
void control_form::ctl_button_check(bool dir,int duty)
{
    if(dir)
    {
        ui->btn_for_1->setEnabled(false);
        ui->btn_re_1->setEnabled(true);
    }
    else
    {
        ui->btn_for_1->setEnabled(true);
        ui->btn_re_1->setEnabled(false);
    }
    if(duty==0)
    {
        ui->btn_stop_1->setEnabled(false);
        ui->btn_fifty_1->setEnabled(true);
        ui->btn_twenty_1->setEnabled(true);
        ui->btn_seventy_1->setEnabled(true);

    }
    else if(duty==1)
    {
        ui->btn_stop_1->setEnabled(true);
        ui->btn_fifty_1->setEnabled(true);
        ui->btn_twenty_1->setEnabled(false);
        ui->btn_seventy_1->setEnabled(true);
    }
    else if(duty==2)
    {
        ui->btn_stop_1->setEnabled(true);
        ui->btn_fifty_1->setEnabled(false);
        ui->btn_twenty_1->setEnabled(true);
        ui->btn_seventy_1->setEnabled(true);
    }
    else if(duty==3)
    {
        ui->btn_stop_1->setEnabled(true);
        ui->btn_fifty_1->setEnabled(true);
        ui->btn_twenty_1->setEnabled(true);
        ui->btn_seventy_1->setEnabled(false);
    }
}


// SET
void control_form::all_set()
{
    loading *l = new loading();
    l->show();
    Widget::delay_msec(3000);

    dir=1;
    duty=0;

    ctl_button_check(dir,duty);

    system("/home/icdyeing/mqtt/1pub_ctl.sh 0 1");


    l->close();
    delete l;

}


void control_form::dir_set(bool a)
{
    loading *l = new loading();
    l->show();
    Widget::delay_msec(3000);

    dir=a;

    sub->sub_cmd_break();

    if(a)
    {
        system("/home/icdyeing/mqtt/1pub_ctl.sh -1 1");
    }
    else
    {
        system("/home/icdyeing/mqtt/1pub_ctl.sh -1 0");
    }

    ctl_button_check(dir,duty);

    //p->startDetached("/home/icdyeing/mqtt/1sub_cmd.sh");
    emit sub->sub_start();

    l->close();
    delete l;


}

int control_form::duty_set(int a)
{
    loading *l = new loading();
    l->show();
    Widget::delay_msec(3000);

    duty=a;

    sub->sub_cmd_break();

    if(a==0)
    {
        system("/home/icdyeing/mqtt/1pub_ctl.sh 0 -1");
    }
    else if(a==1)
    {
        system("/home/icdyeing/mqtt/1pub_ctl.sh 1 -1");
    }
    else if(a==2)
    {
        system("/home/icdyeing/mqtt/1pub_ctl.sh 2 -1");
    }
    else if(a==3)
    {
        system("/home/icdyeing/mqtt/1pub_ctl.sh 3 -1");
    }
    else
    {
        return -1;
    }

    ctl_button_check(dir,duty);

    //p->startDetached("/home/icdyeing/mqtt/1sub_cmd.sh");
    emit sub->sub_start();

    l->close();
    delete l;



    return 0;
}


// SIGNAL

void control_form::on_control_back_clicked()
{
    Widget *widget = new Widget();
    this->close();
    delete this;
    widget->show();
}


void control_form::on_btn_for_1_clicked()
{
    dir_set(1);
}

void control_form::on_btn_re_1_clicked()
{
    dir_set(0);
}


void control_form::on_btn_twenty_1_clicked()
{
    duty_set(1);
}

void control_form::on_btn_fifty_1_clicked()
{
    duty_set(2);
}

void control_form::on_btn_seventy_1_clicked()
{
    duty_set(3);
}

void control_form::on_btn_stop_1_clicked()
{
    duty_set(0);
}
