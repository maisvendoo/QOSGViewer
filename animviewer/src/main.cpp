#include    "mainwindow.h"
#include    <QApplication>
#include    <QTranslator>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;

    if (translator.load(QLocale(),
                        QLatin1String("QOSGViewer"),
                        QLatin1String("."),
                        QLatin1String(":/translations/translations"),
                        QLatin1String(".qm")))

        app.installTranslator(&translator);

    MainWindow window;
    window.show();

    return app.exec();
}
