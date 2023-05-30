#ifndef WIDGET_H
#define WIDGET_H


#include <auto_form.h>
#include <control_form.h>
#include <monitor_form.h>
#include <info_form.h>
#include <loading.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <QProcess>
#include <qstring.h>

#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QObject>

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QFile>
#include <QVBoxLayout>
#include <QHBoxLayout>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

// par
extern bool dir;
extern int duty;

extern bool tem_auto_temperature;
extern bool tem_auto_humidity;
extern bool tem_auto_smoke;

extern QFile file;
extern QProcess *p;
extern QStringList list;

// thread
class sub_sub;
extern QThread sub_thread;
extern sub_sub *sub;


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    static void delay_msec(unsigned int msec);

private slots:
    void on_auto_btn_clicked();

    void on_monitor_btn_clicked();

    void on_contorl_btn_clicked();

    void on_info_btn_clicked();

    void on_closebtn_clicked();

private:
    Ui::Widget *ui;


};


class sub_sub : public QObject
{
    Q_OBJECT

private:
    QMutex lock;

    bool iscanrun;
    bool sub_out;

public slots:
    void sub_cmd();

public:
    void sub_cmd_break();

signals:
    void sub_start();
};


#endif // WIDGET_H

