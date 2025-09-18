/********************************************************************************
** Form generated from reading UI file 'getdata.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETDATA_H
#define UI_GETDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_getdata
{
public:
    QTabWidget *tabWidget;
    QWidget *tabWidgetPage1;
    QGridLayout *gridLayout_2;
    QLabel *label_speed1Speed;
    QLineEdit *lineedit_speed;
    QLineEdit *lineedit_turns;
    QLabel *label_turns;
    QLineEdit *lineedit_mode;
    QLabel *label_voltage;
    QLabel *label_mode;
    QLineEdit *lineedit_speed1Speed;
    QLabel *label_speed;
    QLabel *label_speedRef;
    QLabel *label_IqRef;
    QLineEdit *lineedit_voltage;
    QLineEdit *lineedit_IqRef;
    QLineEdit *lineedit_speedRef;

    void setupUi(QWidget *getdata)
    {
        if (getdata->objectName().isEmpty())
            getdata->setObjectName(QString::fromUtf8("getdata"));
        getdata->resize(1125, 623);
        tabWidget = new QTabWidget(getdata);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 700, 360));
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName(QString::fromUtf8("tabWidgetPage1"));
        gridLayout_2 = new QGridLayout(tabWidgetPage1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_speed1Speed = new QLabel(tabWidgetPage1);
        label_speed1Speed->setObjectName(QString::fromUtf8("label_speed1Speed"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_speed1Speed->setFont(font);

        gridLayout_2->addWidget(label_speed1Speed, 4, 0, 1, 1);

        lineedit_speed = new QLineEdit(tabWidgetPage1);
        lineedit_speed->setObjectName(QString::fromUtf8("lineedit_speed"));

        gridLayout_2->addWidget(lineedit_speed, 13, 1, 1, 1);

        lineedit_turns = new QLineEdit(tabWidgetPage1);
        lineedit_turns->setObjectName(QString::fromUtf8("lineedit_turns"));

        gridLayout_2->addWidget(lineedit_turns, 6, 1, 1, 1);

        label_turns = new QLabel(tabWidgetPage1);
        label_turns->setObjectName(QString::fromUtf8("label_turns"));
        label_turns->setFont(font);

        gridLayout_2->addWidget(label_turns, 6, 0, 1, 1);

        lineedit_mode = new QLineEdit(tabWidgetPage1);
        lineedit_mode->setObjectName(QString::fromUtf8("lineedit_mode"));

        gridLayout_2->addWidget(lineedit_mode, 12, 1, 1, 1);

        label_voltage = new QLabel(tabWidgetPage1);
        label_voltage->setObjectName(QString::fromUtf8("label_voltage"));
        label_voltage->setFont(font);

        gridLayout_2->addWidget(label_voltage, 14, 0, 1, 1);

        label_mode = new QLabel(tabWidgetPage1);
        label_mode->setObjectName(QString::fromUtf8("label_mode"));
        label_mode->setFont(font);

        gridLayout_2->addWidget(label_mode, 12, 0, 1, 1);

        lineedit_speed1Speed = new QLineEdit(tabWidgetPage1);
        lineedit_speed1Speed->setObjectName(QString::fromUtf8("lineedit_speed1Speed"));

        gridLayout_2->addWidget(lineedit_speed1Speed, 4, 1, 1, 1);

        label_speed = new QLabel(tabWidgetPage1);
        label_speed->setObjectName(QString::fromUtf8("label_speed"));
        label_speed->setFont(font);

        gridLayout_2->addWidget(label_speed, 13, 0, 1, 1);

        label_speedRef = new QLabel(tabWidgetPage1);
        label_speedRef->setObjectName(QString::fromUtf8("label_speedRef"));
        label_speedRef->setFont(font);

        gridLayout_2->addWidget(label_speedRef, 3, 0, 1, 1);

        label_IqRef = new QLabel(tabWidgetPage1);
        label_IqRef->setObjectName(QString::fromUtf8("label_IqRef"));
        label_IqRef->setFont(font);

        gridLayout_2->addWidget(label_IqRef, 1, 0, 1, 1);

        lineedit_voltage = new QLineEdit(tabWidgetPage1);
        lineedit_voltage->setObjectName(QString::fromUtf8("lineedit_voltage"));

        gridLayout_2->addWidget(lineedit_voltage, 14, 1, 1, 1);

        lineedit_IqRef = new QLineEdit(tabWidgetPage1);
        lineedit_IqRef->setObjectName(QString::fromUtf8("lineedit_IqRef"));

        gridLayout_2->addWidget(lineedit_IqRef, 1, 1, 1, 1);

        lineedit_speedRef = new QLineEdit(tabWidgetPage1);
        lineedit_speedRef->setObjectName(QString::fromUtf8("lineedit_speedRef"));

        gridLayout_2->addWidget(lineedit_speedRef, 3, 1, 1, 1);

        tabWidget->addTab(tabWidgetPage1, QString());

        retranslateUi(getdata);

        QMetaObject::connectSlotsByName(getdata);
    } // setupUi

    void retranslateUi(QWidget *getdata)
    {
        getdata->setWindowTitle(QApplication::translate("getdata", "Form", nullptr));
        label_speed1Speed->setText(QApplication::translate("getdata", "\345\256\236\351\231\205\350\275\254\351\200\237\357\274\232", nullptr));
        label_turns->setText(QApplication::translate("getdata", "\346\227\213\350\275\254\345\234\210\346\225\260\357\274\232", nullptr));
        label_voltage->setText(QApplication::translate("getdata", "\346\257\215\347\272\277\347\224\265\345\216\213\357\274\232", nullptr));
        label_mode->setText(QApplication::translate("getdata", "\350\277\220\350\241\214\346\250\241\345\274\217\357\274\232", nullptr));
        label_speed->setText(QApplication::translate("getdata", "\347\224\265\346\234\272\350\275\254\351\200\237\357\274\232", nullptr));
        label_speedRef->setText(QApplication::translate("getdata", "\350\276\223\345\205\245\350\275\254\351\200\237\357\274\232", nullptr));
        label_IqRef->setText(QApplication::translate("getdata", "Q\350\275\264\347\224\265\346\265\201\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage1), QString());
    } // retranslateUi

};

namespace Ui {
    class getdata: public Ui_getdata {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETDATA_H
