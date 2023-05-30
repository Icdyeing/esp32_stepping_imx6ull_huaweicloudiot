#include "widget.h"
#include <auto_form.h>
#include <control_form.h>
#include <monitor_form.h>
#include <info_form.h>
#include <loading.h>

#include <QApplication>
#include <qthread.h>
#include <QProcess>

bool tem_auto_humidity;
bool tem_auto_smoke;
bool tem_auto_temperature;
bool dir;
int duty;
QFile file;
sub_sub *sub = new sub_sub();
QThread sub_thread;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    loading *l=new loading();
    l->show();
    Widget::delay_msec(3000);

    //MQTT LOADING
    // auto set
    auto_form *au = new auto_form();
    au->auto_set_all();// set temper,humid,smoke 1
    delete au;

    // ctl set
    control_form *co = new control_form();
    co->all_set();// ste dir 1,duty 0
    delete co;


    sub->moveToThread(&sub_thread);
    sub_thread.start();
    //sub->sub_cmd();
    emit sub->sub_start();

    l->close();
    delete l;

    w.show();

    return a.exec();
}

