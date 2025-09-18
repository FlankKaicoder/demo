#-------------------------------------------------
#
# Project created by QtCreator 2023-03-04T16:52:48
#
#-------------------------------------------------
QT       += sql            #数据库
QT       += core gui sql   #图形用户界面gui
QT       += widgets        #小部件模块
QT       += core gui serialport #串口
QT       += printsupport        #打印支持
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET =   ClassRoom#生成可执行文件的名称TARGET = LOGIN
TEMPLATE = app

RC_FILE = myapp.rc

RC_ICONS = login.ico

DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += main.cpp\
    appinit.cpp \
    iconhelper.cpp \
    login.cpp \
    passwdedit.cpp \
    qcustomplot.cpp \
    register.cpp \
    systemtrayicon.cpp \
    mainwindow.cpp

HEADERS  += \
    appinit.h \
    iconhelper.h \
    mainwindow.h \
    login.h \
    passwdedit.h \
    qcustomplot.h \
    register.h \
    systemtrayicon.h

FORMS    += \
    login.ui \
    passwdedit.ui \
    register.ui \
    mainwindow.ui

RESOURCES += \
    myqrc.qrc \
    lang.qrc \
    qss.qrc

TRANSLATIONS+=cn.ts\
              en.ts

#CONFIG += console

DISTFILES += \
    images/ico/user1.png
