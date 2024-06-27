#include "sudoku.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QWidget>
#include <QKeyEvent>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QIcon *icon = new QIcon(":/icons/icon.ico");
    a.setWindowIcon(*icon);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Sudoku_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    Sudoku w;

    w.show();
    return a.exec();
}
