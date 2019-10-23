#include "admgeneral.h"
#include "ui_admgeneral.h"

admGeneral::admGeneral(QString user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admGeneral)
{
    ui->setupUi(this);
}

admGeneral::~admGeneral()
{
    delete ui;
}
