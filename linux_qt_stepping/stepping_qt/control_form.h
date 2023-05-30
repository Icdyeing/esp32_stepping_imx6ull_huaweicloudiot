#ifndef CONTROL_FORM_H
#define CONTROL_FORM_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class control_form;
}

class control_form : public QWidget
{
    Q_OBJECT

public:
    explicit control_form(QWidget *parent = nullptr);
    ~control_form();

    // set
    void dir_set(bool a);
    int duty_set(int a);
    void all_set();

    // check
    void ctl_button_check(bool dir,int duty);

private slots:
    void on_control_back_clicked();

    void on_btn_for_1_clicked();

    void on_btn_re_1_clicked();

    void on_btn_twenty_1_clicked();

    void on_btn_fifty_1_clicked();

    void on_btn_seventy_1_clicked();

    void on_btn_stop_1_clicked();

private:
    Ui::control_form *ui;
};

#endif // CONTROL_FORM_H
