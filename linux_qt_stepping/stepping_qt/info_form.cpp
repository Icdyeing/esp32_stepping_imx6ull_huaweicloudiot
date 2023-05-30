#include "info_form.h"
#include "ui_info_form.h"
#include <widget.h>

info_form::info_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::info_form)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgba(196, 255, 242, 100%);");
}

info_form::~info_form()
{
    delete ui;
}

void info_form::on_info_back_clicked()
{
    Widget *widget = new Widget();
    this->close();
    delete this;
    widget->show();
}
