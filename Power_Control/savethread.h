#ifndef SAVETHREAD_H
#define SAVETHREAD_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <QTimer>

class SaveThread:public QThread
{
    Q_OBJECT
public:
    SaveThread(QString &saveImagePath,int &saveCheck,int &saveNum,QImage &fImage,int &time_int);//主线程与子线程交互数据的构造函数
    void run() ;
private:
    //声明用来接收主线程的变量
    QString saveImagePath_s;
    QString sttr;
    int saveCheck_s;
    int saveNum_s;
    QImage fImage_s;
    int time_int_s;
    int pro_time_s;
    int pro_num = 0;
signals:
    void isDone();
};

#endif // SAVETHREAD_H
