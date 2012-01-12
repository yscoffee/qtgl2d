/********************************************************************************
** Form generated from reading UI file 'gameControlWidget.ui'
**
** Created: Thu Jan 12 11:16:06 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMECONTROLWIDGET_H
#define UI_GAMECONTROLWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameControlWidget
{
public:

    void setupUi(QWidget *GameControlWidget)
    {
        if (GameControlWidget->objectName().isEmpty())
            GameControlWidget->setObjectName(QString::fromUtf8("GameControlWidget"));
        GameControlWidget->resize(800, 600);
        GameControlWidget->setMinimumSize(QSize(800, 600));
        GameControlWidget->setBaseSize(QSize(800, 600));

        retranslateUi(GameControlWidget);

        QMetaObject::connectSlotsByName(GameControlWidget);
    } // setupUi

    void retranslateUi(QWidget *GameControlWidget)
    {
        GameControlWidget->setWindowTitle(QApplication::translate("GameControlWidget", "MainWidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GameControlWidget: public Ui_GameControlWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMECONTROLWIDGET_H
