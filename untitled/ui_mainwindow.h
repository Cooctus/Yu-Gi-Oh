/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *titleFrame;
    QLabel *title;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 500);
        MainWindow->setStyleSheet(QLatin1String("QWidget#centralWidget{\n"
"	background-color: #196D8D;\n"
"\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        titleFrame = new QFrame(centralWidget);
        titleFrame->setObjectName(QStringLiteral("titleFrame"));
        titleFrame->setGeometry(QRect(0, 0, 1001, 51));
        titleFrame->setStyleSheet(QLatin1String("QFrame#titleFrame {\n"
"	background-color: #11465B;\n"
"	border: none;\n"
"}"));
        titleFrame->setFrameShape(QFrame::StyledPanel);
        titleFrame->setFrameShadow(QFrame::Raised);
        title = new QLabel(titleFrame);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(10, 10, 201, 31));
        title->setStyleSheet(QLatin1String("QLabel{\n"
"font: 14pt \"Kiona\";\n"
"color: #196D8D;\n"
"}"));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        title->setText(QApplication::translate("MainWindow", "Cooctus/Yu-Gi-Oh", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
