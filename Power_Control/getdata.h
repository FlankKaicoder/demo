#ifndef GETDATA_H
#define GETDATA_H

#include <QWidget>

namespace Ui {
class getdata;
}

class getdata : public QWidget
{
    Q_OBJECT

public:
    explicit getdata(QWidget *parent = nullptr);
    ~getdata();

private:
    Ui::getdata *ui;
};

#endif // GETDATA_H
