/********************************************************************************
** Form generated from reading UI file 'howtoplay.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOWTOPLAY_H
#define UI_HOWTOPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HowToPlay
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *HowToPlay)
    {
        if (HowToPlay->objectName().isEmpty())
            HowToPlay->setObjectName("HowToPlay");
        HowToPlay->resize(573, 415);
        groupBox = new QGroupBox(HowToPlay);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(240, 0, 331, 410));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 15, 311, 381));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/teach.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(HowToPlay);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(15, 10, 221, 391));
        QFont font;
        font.setPointSize(16);
        label_2->setFont(font);
        label_2->setTextFormat(Qt::AutoText);
        label_2->setWordWrap(true);

        retranslateUi(HowToPlay);

        QMetaObject::connectSlotsByName(HowToPlay);
    } // setupUi

    void retranslateUi(QWidget *HowToPlay)
    {
        HowToPlay->setWindowTitle(QCoreApplication::translate("HowToPlay", "Sudoku - \346\200\216\344\271\210\347\216\251?", nullptr));
        groupBox->setTitle(QCoreApplication::translate("HowToPlay", "\347\225\214\351\235\242\346\246\202\350\247\210", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("HowToPlay", "<html><head/><body><p>1\357\274\232\344\275\277\347\224\250\351\224\256\347\233\230\346\225\260\345\255\227\351\224\256\344\277\256\346\224\271\345\217\263\344\270\212\350\247\222\345\200\231\351\200\211\346\225\260\345\255\227\343\200\202</p><p>2\357\274\232\347\204\266\345\220\216\351\274\240\346\240\207\345\267\246\351\224\256\346\214\211\344\270\213\346\226\271\345\235\227\345\260\206\346\225\260\345\255\227\345\241\253\345\205\245\350\277\233\345\216\273\343\200\202</p><p>3\357\274\232\351\274\240\346\240\207\345\217\263\351\224\256\346\226\271\345\235\227\345\217\257\344\273\245\346\230\276\347\244\272\346\217\220\347\244\272\343\200\202</p><p>4\357\274\232\346\226\271\345\235\227\350\242\253\345\241\253\345\205\245\351\224\231\350\257\257\347\232\204\346\225\260\345\255\227\345\260\206\344\274\232\344\270\242\345\244\261\345\210\206\346\225\260!</p><p>5\357\274\232\344\270\200\350\241\214\344\270\200\345\210\227\344\270\200\345\256\253\346\240\274\344\270\215\345\207\272\347\216\260\351\207\215\345\244\215"
                        "\346\225\260\345\255\227\343\200\202</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HowToPlay: public Ui_HowToPlay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOWTOPLAY_H
