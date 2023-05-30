#ifndef INFO_FORM_H
#define INFO_FORM_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class info_form;
}

class info_form : public QWidget
{
    Q_OBJECT

public:
    explicit info_form(QWidget *parent = nullptr);
    ~info_form();

private slots:
    void on_info_back_clicked();

private:
    Ui::info_form *ui;
};

#endif // INFO_FORM_H
