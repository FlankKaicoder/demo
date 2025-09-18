/********************************************************************************
** Form generated from reading UI file 'caozuojl.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAOZUOJL_H
#define UI_CAOZUOJL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_caozuojl
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QTableWidget *tableWidget;

    void setupUi(QWidget *caozuojl)
    {
        if (caozuojl->objectName().isEmpty())
            caozuojl->setObjectName(QStringLiteral("caozuojl"));
        caozuojl->resize(661, 472);
        gridLayout = new QGridLayout(caozuojl);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(caozuojl);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        tableWidget = new QTableWidget(caozuojl);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        retranslateUi(caozuojl);

        QMetaObject::connectSlotsByName(caozuojl);
    } // setupUi

    void retranslateUi(QWidget *caozuojl)
    {
        caozuojl->setWindowTitle(QApplication::translate("caozuojl", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("caozuojl", "\346\237\245\347\234\213\346\223\215\344\275\234\350\256\260\345\275\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class caozuojl: public Ui_caozuojl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAOZUOJL_H
