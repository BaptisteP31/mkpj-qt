#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "mkpj-qt_" + QLocale(locale).name();
        qDebug() << "Looking for " ":/i18n/" + baseName + " translation file...";
        if (translator.load(":/i18n/" + baseName)) {
            qDebug() << "Found ! translated to " + QLocale(locale).name();
            a.installTranslator(&translator);
            break;
        }
    }

    /*
    // Use this to force a certain traduction on your system
    QTranslator translator;
    if (translator.load(":/i18n/mkpj-qt_<locale>")) {
        a.installTranslator(&translator);
    }
    */

    MainWindow w;
    w.show();
    return a.exec();
}
