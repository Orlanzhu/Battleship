/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QLabel *Field1;
    QLabel *Field2;
    QPushButton *ButtonEnd;
    QPushButton *ButtonNext;
    QLabel *label;
    QLabel *label_2;
    QWidget *gridLayoutWidget;
    QGridLayout *field1;
    QWidget *gridLayoutWidget_2;
    QGridLayout *field2;

    void setupUi(QDialog *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QStringLiteral("GameWindow"));
        GameWindow->resize(1150, 600);
        Field1 = new QLabel(GameWindow);
        Field1->setObjectName(QStringLiteral("Field1"));
        Field1->setGeometry(QRect(50, 100, 401, 401));
        Field1->setFrameShape(QFrame::Box);
        Field2 = new QLabel(GameWindow);
        Field2->setObjectName(QStringLiteral("Field2"));
        Field2->setGeometry(QRect(700, 100, 401, 401));
        Field2->setFrameShape(QFrame::Box);
        ButtonEnd = new QPushButton(GameWindow);
        ButtonEnd->setObjectName(QStringLiteral("ButtonEnd"));
        ButtonEnd->setGeometry(QRect(480, 460, 191, 41));
        ButtonNext = new QPushButton(GameWindow);
        ButtonNext->setObjectName(QStringLiteral("ButtonNext"));
        ButtonNext->setGeometry(QRect(480, 410, 191, 41));
        label = new QLabel(GameWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(480, 150, 191, 251));
        label->setFrameShape(QFrame::Box);
        label_2 = new QLabel(GameWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(480, 100, 191, 41));
        label_2->setFrameShape(QFrame::Box);
        gridLayoutWidget = new QWidget(GameWindow);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(50, 100, 401, 401));
        field1 = new QGridLayout(gridLayoutWidget);
        field1->setSpacing(0);
        field1->setObjectName(QStringLiteral("field1"));
        field1->setSizeConstraint(QLayout::SetDefaultConstraint);
        field1->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_2 = new QWidget(GameWindow);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(700, 100, 401, 401));
        field2 = new QGridLayout(gridLayoutWidget_2);
        field2->setSpacing(0);
        field2->setObjectName(QStringLiteral("field2"));
        field2->setContentsMargins(0, 0, 0, 0);

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QDialog *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "Dialog", 0));
        Field1->setText(QString());
        Field2->setText(QString());
        ButtonEnd->setText(QApplication::translate("GameWindow", "Spiel beenden", 0));
        ButtonNext->setText(QApplication::translate("GameWindow", "N\303\244chste Zug", 0));
        label->setText(QApplication::translate("GameWindow", "Status", 0));
        label_2->setText(QApplication::translate("GameWindow", "Which players turn", 0));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
