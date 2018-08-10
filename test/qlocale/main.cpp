/*
 * This is taken directly from
 * https://doc-snapshots.qt.io/qt-mobility/quickstart.html
 * and then attempted to port to Qt5.11
 */

#include <QApplication>
#include <QLabel>

#include <QLocale> //(1)

// QTM_USE_NAMESPACE //(2)

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLocale s;
    QLabel *label = new QLabel(QObject::tr("hello ").append(s.bcp47Name()));
    label->show();
    label->resize(100,30);
    return app.exec();
}
