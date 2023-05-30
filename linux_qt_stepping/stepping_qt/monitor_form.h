#ifndef MONITOR_FORM_H
#define MONITOR_FORM_H

#include <QWidget>
#include "widget.h"
#include <qfile.h>

namespace Ui {
class monitor_form;
}

class monitor_form : public QWidget
{
    Q_OBJECT

public:
    explicit monitor_form(QWidget *parent = nullptr);
    ~monitor_form();


    // read
    int readFile();

private slots:
    void on_monitor_back_clicked();

    void on_refreshButton_clicked();

    void on_refreshButton2_clicked();

private:
    Ui::monitor_form *ui;
};

#endif // MONITOR_FORM_H
