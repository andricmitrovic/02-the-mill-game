/********************************************************************************
** Form generated from reading UI file 'multiplayermenu.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTIPLAYERMENU_H
#define UI_MULTIPLAYERMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MultiplayerMenu
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *leName;
    QPushButton *connectBtn;
    QLabel *laError;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MultiplayerMenu)
    {
        if (MultiplayerMenu->objectName().isEmpty())
            MultiplayerMenu->setObjectName(QStringLiteral("MultiplayerMenu"));
        MultiplayerMenu->resize(800, 600);
        centralwidget = new QWidget(MultiplayerMenu);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(140, 90, 351, 271));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        leName = new QLineEdit(groupBox_2);
        leName->setObjectName(QStringLiteral("leName"));

        horizontalLayout->addWidget(leName);

        connectBtn = new QPushButton(groupBox_2);
        connectBtn->setObjectName(QStringLiteral("connectBtn"));

        horizontalLayout->addWidget(connectBtn);


        verticalLayout->addWidget(groupBox_2);

        laError = new QLabel(groupBox);
        laError->setObjectName(QStringLiteral("laError"));

        verticalLayout->addWidget(laError);

        MultiplayerMenu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MultiplayerMenu);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MultiplayerMenu->setMenuBar(menubar);
        statusbar = new QStatusBar(MultiplayerMenu);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MultiplayerMenu->setStatusBar(statusbar);

        retranslateUi(MultiplayerMenu);

        QMetaObject::connectSlotsByName(MultiplayerMenu);
    } // setupUi

    void retranslateUi(QMainWindow *MultiplayerMenu)
    {
        MultiplayerMenu->setWindowTitle(QApplication::translate("MultiplayerMenu", "MainWindow", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MultiplayerMenu", "Enter your name: ", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        leName->setText(QString());
        connectBtn->setText(QApplication::translate("MultiplayerMenu", "Connect", Q_NULLPTR));
        laError->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MultiplayerMenu: public Ui_MultiplayerMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTIPLAYERMENU_H
