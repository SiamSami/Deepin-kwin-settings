#include "deepin_kwin_settings.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("dlight");
    deepin_kwin_settings w;
    w.setWindowTitle("Deepin Kwin settings");
    w.show();

    return a.exec();
}
