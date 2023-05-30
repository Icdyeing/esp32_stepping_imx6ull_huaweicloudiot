#include "auto_form.h"
#include "ui_auto_form.h"
#include <widget.h>
#include <qthread.h>


auto_form::auto_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::auto_form)
{
    ui->setupUi(this);
    this->setGeometry(0,0,800,480);
    this->setStyleSheet("background-color: rgba(196, 255, 242, 100%);");
    auto_button_check(tem_auto_temperature,tem_auto_humidity,tem_auto_smoke);
}

auto_form::~auto_form()
{
    delete ui;
}

// check
void auto_form::auto_button_check(bool t,bool h,bool s)
{
    if(t)
    {
        ui->TEM_STOP->setEnabled(true);
        ui->TEM_RUN->setEnabled(false);
    }
    else
    {
        ui->TEM_STOP->setEnabled(false);
        ui->TEM_RUN->setEnabled(true);
    }

    if(s)
    {
        ui->SMK_STOP->setEnabled(true);
        ui->SMK_RUN->setEnabled(false);
    }
    else
    {
        ui->SMK_STOP->setEnabled(false);
        ui->SMK_RUN->setEnabled(true);
    }

    if(h)
    {
        ui->HUD_STOP->setEnabled(true);
        ui->HUD_RUN->setEnabled(false);
    }
    else
    {
        ui->HUD_STOP->setEnabled(false);
        ui->HUD_RUN->setEnabled(true);
    }
}


// SET
void auto_form::auto_set_all()
{
    loading *l = new loading();
    l->show();
    Widget::delay_msec(3000);

    tem_auto_temperature=1;
    tem_auto_smoke=1;
    tem_auto_humidity=1;

    auto_button_check(tem_auto_temperature,tem_auto_humidity,tem_auto_smoke);

    system("/home/icdyeing/mqtt/1pub_auto.sh 1 1 1");

    //p->startDetached("/home/icdyeing/mqtt/1sub_cmd.sh");

    l->close();
    delete l;
}

void auto_form::auto_set_temper(bool a)
{
    loading *l = new loading();
    l->show();
    Widget::delay_msec(3000);

    tem_auto_temperature=a;

    sub->sub_cmd_break();

    if(a)
    {
        system("/home/icdyeing/mqtt/1pub_auto.sh 1 -1 -1");
    }
    else
    {
        system("/home/icdyeing/mqtt/1pub_auto.sh 0 -1 -1");
    }

    auto_button_check(tem_auto_temperature,tem_auto_humidity,tem_auto_smoke);

    //p->startDetached("/home/icdyeing/mqtt/1sub_cmd.sh");
    emit sub->sub_start();

    l->close();
    delete l;
}

void auto_form::auto_set_humid(bool a)
{
    loading *l = new loading();
    l->show();
    Widget::delay_msec(3000);

    tem_auto_humidity=a;

    sub->sub_cmd_break();

    if(a)
    {
        system("/home/icdyeing/mqtt/1pub_auto.sh -1 1 -1");
    }
    else
    {
        system("/home/icdyeing/mqtt/1pub_auto.sh -1 0 -1");
    }

    auto_button_check(tem_auto_temperature,tem_auto_humidity,tem_auto_smoke);

    //p->startDetached("/home/icdyeing/mqtt/1sub_cmd.sh");
    emit sub->sub_start();

    l->close();
    delete l;
}

void auto_form::auto_set_smoke(bool a)
{
    loading *l = new loading();
    l->show();
    Widget::delay_msec(3000);

    tem_auto_smoke=a;

    sub->sub_cmd_break();

    if(a)
    {
        system("/home/icdyeing/mqtt/1pub_auto.sh -1 -1 1");
    }
    else
    {
        system("/home/icdyeing/mqtt/1pub_auto.sh -1 -1 0");
    }

    auto_button_check(tem_auto_temperature,tem_auto_humidity,tem_auto_smoke);

    //p->startDetached("/home/icdyeing/mqtt/1sub_cmd.sh");
    emit sub->sub_start();

    l->close();
    delete l;
}


// SIGNAL
void auto_form::on_auto_back_clicked()
{
    Widget *widget = new Widget();
    this->close();
    delete this;
    widget->show();
}

// smk_btn
void auto_form::on_SMK_RUN_clicked()
{
    auto_set_smoke(1);
}

void auto_form::on_SMK_STOP_clicked()
{
    auto_set_smoke(0);
}

// tem_btn
void auto_form::on_TEM_RUN_clicked()
{
    auto_form::auto_set_temper(1);
}

void auto_form::on_TEM_STOP_clicked()
{
    auto_form::auto_set_temper(0);
}

// humid_btn
void auto_form::on_HUD_RUN_clicked()
{
    auto_set_humid(1);
}

void auto_form::on_HUD_STOP_clicked()
{
    auto_set_humid(0);
}

