#include "savethread.h"
#include <QDebug>
#include <QDateTime>
//构造函数的实现，进行参数的传递
SaveThread::SaveThread(QString &saveImagePath,int &saveCheck,int &saveNum,QImage &fImage,int &time_int)
{
    saveImagePath_s = saveImagePath;
    saveCheck_s = saveCheck;
    saveNum_s = saveNum;
    fImage_s = fImage;
    time_int_s = time_int;

}
void SaveThread::run()
{
    qDebug()<<"调用了一次多线程";
}
