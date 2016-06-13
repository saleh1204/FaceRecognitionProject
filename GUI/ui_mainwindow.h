/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *uploadTest;
    QPushButton *testBt;
    QPushButton *uploadTraning;
    QGraphicsView *img1;
    QGraphicsView *img2;
    QLabel *label;
    QLabel *status_lbl;
    QLabel *mispredicted_lbl;
    QLabel *unpredicted_lbl;
    QLabel *predictedLabel_lbl;
    QLabel *confidence_lbl;
    QLabel *totalTestingImageNumber_lbl;
    QMenuBar *menuBar;
    QMenu *menuFace_Recognition_for_COE_487;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(770, 705);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        uploadTest = new QPushButton(centralWidget);
        uploadTest->setObjectName(QString::fromUtf8("uploadTest"));
        uploadTest->setGeometry(QRect(160, 590, 141, 27));
        testBt = new QPushButton(centralWidget);
        testBt->setObjectName(QString::fromUtf8("testBt"));
        testBt->setGeometry(QRect(370, 590, 99, 27));
        uploadTraning = new QPushButton(centralWidget);
        uploadTraning->setObjectName(QString::fromUtf8("uploadTraning"));
        uploadTraning->setGeometry(QRect(530, 590, 151, 27));
        img1 = new QGraphicsView(centralWidget);
        img1->setObjectName(QString::fromUtf8("img1"));
        img1->setGeometry(QRect(20, 80, 351, 361));
        img2 = new QGraphicsView(centralWidget);
        img2->setObjectName(QString::fromUtf8("img2"));
        img2->setGeometry(QRect(405, 80, 341, 361));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(300, 20, 200, 50));
        QFont font;
        font.setPointSize(17);
        label->setFont(font);
        status_lbl = new QLabel(centralWidget);
        status_lbl->setObjectName(QString::fromUtf8("status_lbl"));
        status_lbl->setGeometry(QRect(10, 620, 371, 17));
        mispredicted_lbl = new QLabel(centralWidget);
        mispredicted_lbl->setObjectName(QString::fromUtf8("mispredicted_lbl"));
        mispredicted_lbl->setGeometry(QRect(40, 450, 261, 17));
        unpredicted_lbl = new QLabel(centralWidget);
        unpredicted_lbl->setObjectName(QString::fromUtf8("unpredicted_lbl"));
        unpredicted_lbl->setGeometry(QRect(40, 480, 251, 17));
        predictedLabel_lbl = new QLabel(centralWidget);
        predictedLabel_lbl->setObjectName(QString::fromUtf8("predictedLabel_lbl"));
        predictedLabel_lbl->setGeometry(QRect(40, 510, 251, 17));
        confidence_lbl = new QLabel(centralWidget);
        confidence_lbl->setObjectName(QString::fromUtf8("confidence_lbl"));
        confidence_lbl->setGeometry(QRect(40, 570, 241, 17));
        totalTestingImageNumber_lbl = new QLabel(centralWidget);
        totalTestingImageNumber_lbl->setObjectName(QString::fromUtf8("totalTestingImageNumber_lbl"));
        totalTestingImageNumber_lbl->setGeometry(QRect(40, 540, 281, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 770, 25));
        menuFace_Recognition_for_COE_487 = new QMenu(menuBar);
        menuFace_Recognition_for_COE_487->setObjectName(QString::fromUtf8("menuFace_Recognition_for_COE_487"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFace_Recognition_for_COE_487->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        uploadTest->setText(QApplication::translate("MainWindow", "Uplad test images", 0, QApplication::UnicodeUTF8));
        testBt->setText(QApplication::translate("MainWindow", "Match", 0, QApplication::UnicodeUTF8));
        uploadTraning->setText(QApplication::translate("MainWindow", "Upload training set", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Face Recognition", 0, QApplication::UnicodeUTF8));
        status_lbl->setText(QApplication::translate("MainWindow", "Status: TEST", 0, QApplication::UnicodeUTF8));
        mispredicted_lbl->setText(QApplication::translate("MainWindow", "Mispredicted", 0, QApplication::UnicodeUTF8));
        unpredicted_lbl->setText(QApplication::translate("MainWindow", "Unpredicted", 0, QApplication::UnicodeUTF8));
        predictedLabel_lbl->setText(QApplication::translate("MainWindow", "Predicted Label", 0, QApplication::UnicodeUTF8));
        confidence_lbl->setText(QApplication::translate("MainWindow", "Confidence", 0, QApplication::UnicodeUTF8));
        totalTestingImageNumber_lbl->setText(QApplication::translate("MainWindow", "Total Number of Tested Images ", 0, QApplication::UnicodeUTF8));
        menuFace_Recognition_for_COE_487->setTitle(QApplication::translate("MainWindow", "Face Recognition for COE 487", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
