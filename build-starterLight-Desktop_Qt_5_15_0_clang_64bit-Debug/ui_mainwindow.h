/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <meshviewerwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_chargement;
    QPushButton *pushButton_H;
    QPushButton *pushButton_K;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *pushButton_2;
    QPushButton *pushButton_AF;
    QPushButton *pushButton;
    QPushButton *pushButton_angleArea;
    MeshViewerWidget *displayWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(632, 408);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(150);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        widget_2->setMinimumSize(QSize(150, 0));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(4);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        pushButton_chargement = new QPushButton(widget_2);
        pushButton_chargement->setObjectName(QString::fromUtf8("pushButton_chargement"));
        pushButton_chargement->setMinimumSize(QSize(200, 0));

        verticalLayout->addWidget(pushButton_chargement);

        pushButton_H = new QPushButton(widget_2);
        pushButton_H->setObjectName(QString::fromUtf8("pushButton_H"));

        verticalLayout->addWidget(pushButton_H);

        pushButton_K = new QPushButton(widget_2);
        pushButton_K->setObjectName(QString::fromUtf8("pushButton_K"));

        verticalLayout->addWidget(pushButton_K);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        lineEdit = new QLineEdit(widget_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(lineEdit);

        doubleSpinBox = new QDoubleSpinBox(widget_2);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        sizePolicy1.setHeightForWidth(doubleSpinBox->sizePolicy().hasHeightForWidth());
        doubleSpinBox->setSizePolicy(sizePolicy1);
        doubleSpinBox->setWrapping(false);

        verticalLayout->addWidget(doubleSpinBox);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_AF = new QPushButton(widget_2);
        pushButton_AF->setObjectName(QString::fromUtf8("pushButton_AF"));

        verticalLayout->addWidget(pushButton_AF);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_angleArea = new QPushButton(widget_2);
        pushButton_angleArea->setObjectName(QString::fromUtf8("pushButton_angleArea"));

        verticalLayout->addWidget(pushButton_angleArea);


        horizontalLayout->addWidget(widget_2);

        displayWidget = new MeshViewerWidget(centralWidget);
        displayWidget->setObjectName(QString::fromUtf8("displayWidget"));

        horizontalLayout->addWidget(displayWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 632, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_chargement->setText(QCoreApplication::translate("MainWindow", "Charger OBJ", nullptr));
        pushButton_H->setText(QCoreApplication::translate("MainWindow", "Courbure Moyenne", nullptr));
        pushButton_K->setText(QCoreApplication::translate("MainWindow", "Courbure Gaussienne", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "Marge erreur", nullptr));
#if QT_CONFIG(accessibility)
        doubleSpinBox->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Angles diedre", nullptr));
        pushButton_AF->setText(QCoreApplication::translate("MainWindow", "Frequence des aires", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Afficher points et faces", nullptr));
        pushButton_angleArea->setText(QCoreApplication::translate("MainWindow", "Test angles/aires", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
