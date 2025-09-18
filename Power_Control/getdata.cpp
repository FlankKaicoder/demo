#include "getdata.h"
#include "ui_getdata.h"

getdata::getdata(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::getdata)
{
    ui->setupUi(this);
}

getdata::~getdata()
{
    delete ui;
}
