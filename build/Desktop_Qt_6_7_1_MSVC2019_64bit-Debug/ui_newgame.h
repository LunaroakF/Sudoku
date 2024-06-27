/********************************************************************************
** Form generated from reading UI file 'newgame.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWGAME_H
#define UI_NEWGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newgame
{
public:
    QGroupBox *groupBox;
    QPushButton *master;
    QPushButton *higher;
    QPushButton *newbee;
    QPushButton *diy;
    QLabel *label;

    void setupUi(QWidget *newgame)
    {
        if (newgame->objectName().isEmpty())
            newgame->setObjectName("newgame");
        newgame->resize(216, 273);
        groupBox = new QGroupBox(newgame);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 0, 198, 221));
        groupBox->setAlignment(Qt::AlignCenter);
        master = new QPushButton(groupBox);
        master->setObjectName("master");
        master->setGeometry(QRect(42, 120, 111, 41));
        higher = new QPushButton(groupBox);
        higher->setObjectName("higher");
        higher->setGeometry(QRect(42, 70, 111, 41));
        newbee = new QPushButton(groupBox);
        newbee->setObjectName("newbee");
        newbee->setGeometry(QRect(42, 20, 111, 41));
        diy = new QPushButton(groupBox);
        diy->setObjectName("diy");
        diy->setGeometry(QRect(42, 170, 111, 41));
        label = new QLabel(newgame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 220, 201, 51));
        label->setScaledContents(false);
        label->setWordWrap(true);

        retranslateUi(newgame);

        QMetaObject::connectSlotsByName(newgame);
    } // setupUi

    void retranslateUi(QWidget *newgame)
    {
        newgame->setWindowTitle(QCoreApplication::translate("newgame", "\351\232\276\345\272\246", nullptr));
        groupBox->setTitle(QCoreApplication::translate("newgame", "\351\232\276\345\272\246\351\200\211\346\213\251", nullptr));
        master->setText(QCoreApplication::translate("newgame", "\345\244\247\345\270\210", nullptr));
        higher->setText(QCoreApplication::translate("newgame", "\351\253\230\346\211\213", nullptr));
        newbee->setText(QCoreApplication::translate("newgame", "\350\220\214\346\226\260", nullptr));
        diy->setText(QCoreApplication::translate("newgame", "\350\207\252\345\256\232\344\271\211", nullptr));
        label->setText(QCoreApplication::translate("newgame", "*\350\220\214\346\226\260\343\200\201\351\253\230\346\211\213\343\200\201\345\244\247\345\270\210\351\232\276\345\272\246\351\242\204\347\225\231\347\251\272\344\275\215\344\276\235\346\254\241\345\242\236\345\244\232\357\274\214\351\232\217\344\271\213\351\242\204\347\225\231\346\227\266\351\227\264\344\271\237\344\274\232\345\242\236\345\244\232\357\274\214\350\207\252\345\256\232\344\271\211\346\270\270\346\210\217\351\273\230\350\256\244\346\227\266\351\227\264550\347\247\222\343\200\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newgame: public Ui_newgame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWGAME_H
