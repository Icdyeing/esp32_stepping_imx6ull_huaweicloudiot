#ifndef AUTO_FORM_H
#define AUTO_FORM_H

#include <QWidget>
#include <control_form.h>
#include <monitor_form.h>
#include <info_form.h>
#include <widget.h>
#include <QPushButton>

namespace Ui {
class auto_form;
}

class auto_form : public QWidget
{
    Q_OBJECT

public:
    explicit auto_form(QWidget *parent = nullptr);
    ~auto_form();

    // set
    void auto_set_temper(bool a);
    void auto_set_humid(bool a);
    void auto_set_smoke(bool a);
    void auto_set_all();

    // check
    void auto_button_check(bool t,bool h,bool s);

private slots:
    void on_auto_back_clicked();

    void on_SMK_RUN_clicked();
    void on_SMK_STOP_clicked();

    void on_TEM_STOP_clicked();
    void on_TEM_RUN_clicked();

    void on_HUD_STOP_clicked();
    void on_HUD_RUN_clicked();

private:
    Ui::auto_form *ui;
};



#endif // AUTO_FORM_H


