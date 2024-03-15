/********************************************************************************
** Form generated from reading UI file 'Lab10.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB10_H
#define UI_LAB10_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab10Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lab10Class)
    {
        if (Lab10Class->objectName().isEmpty())
            Lab10Class->setObjectName("Lab10Class");
        Lab10Class->resize(600, 400);
        menuBar = new QMenuBar(Lab10Class);
        menuBar->setObjectName("menuBar");
        Lab10Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lab10Class);
        mainToolBar->setObjectName("mainToolBar");
        Lab10Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lab10Class);
        centralWidget->setObjectName("centralWidget");
        Lab10Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lab10Class);
        statusBar->setObjectName("statusBar");
        Lab10Class->setStatusBar(statusBar);

        retranslateUi(Lab10Class);

        QMetaObject::connectSlotsByName(Lab10Class);
    } // setupUi

    void retranslateUi(QMainWindow *Lab10Class)
    {
        Lab10Class->setWindowTitle(QCoreApplication::translate("Lab10Class", "Lab10", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab10Class: public Ui_Lab10Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB10_H
