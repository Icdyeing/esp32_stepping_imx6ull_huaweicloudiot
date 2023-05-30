#include "monitor_form.h"
#include "ui_monitor_form.h"
#include <widget.h>
#include <auto_form.h>
#include <control_form.h>
#include <info_form.h>
#include <qthread.h>


monitor_form::monitor_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::monitor_form)
{
    ui->setupUi(this);
    this->setGeometry(0,0,800,480);
    this->setStyleSheet("background-color: rgba(196, 255, 242, 100%);");
    ui->refreshButton->setStyleSheet("QPushButton{qproperty-icon:url(/home/icdyeing/four_stepping/icon/refresh.png)}");
    ui->refreshButton2->setStyleSheet("QPushButton{qproperty-icon:url(/home/icdyeing/four_stepping/icon/refresh.png)}");
    readFile();
}

monitor_form::~monitor_form()
{
    delete ui;
}

void monitor_form::on_monitor_back_clicked()
{
    Widget *widget = new Widget();
    this->close();
    delete this;
    widget->show();
}

// read
int monitor_form::readFile()
{
    // temperture
    file.setFileName("/home/icdyeing/mqtt/step1_temper.txt");
    if(!file.exists())
    {
        ui->lineEdit_tem1->setText("NULL");
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        return -1;
    }
    ui->lineEdit_tem1->setText(file.readAll());
    file.close();

    // humidity
    file.setFileName("/home/icdyeing/mqtt/step1_humid.txt");
    if(!file.exists())
    {
        ui->lineEdit_hud1->setText("NULL");
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        return -1;
    }
    ui->lineEdit_hud1->setText(file.readAll());
    file.close();

    return 0;
}

void monitor_form::on_refreshButton_clicked()
{
    readFile();
}

void monitor_form::on_refreshButton2_clicked()
{
    //NULL
}
