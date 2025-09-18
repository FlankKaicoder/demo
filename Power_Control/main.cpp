#include <QApplication>  //定义QApplication类，在Qt Widgets应用程序中管理GUI程序的控制流和主要设置
                         //继承关系QObject----QCoreApplication---QGuiApplication--QApplication
#include <QtWidgets>
#include "login.h"
#include "mainwindow.h"
#include "appinit.h"

#include <QTextCodec>  //中文显示的头文件

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//argc  -> argument count    argv  ->argument vector
                               //a是QApplication类的实例对象，任何Qt的窗口系统部件被使用之前必须一 个创建QApplication对象
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    a.setWindowIcon(QIcon(":/images/ico/login.ico"));

    AppInit::Instance()->start();

    Login w;   //创建一个对话框对象，即Login实例对象
 //   MainWindow w;
    w.show();   //在创建一个窗口部件的时候，默认是不可见的，必须用show()函数使之变成可见

    return a.exec();//程序进入消息循环，等待可能输入进行响应。这里就是main()把控制权转交给Qt，Qt完成事件处理后，当应用程序退出时，exec()的值就会返回。
}
