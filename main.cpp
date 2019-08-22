#include "deepin_kwin_settings.h"
#include <DApplication>
#include <DAboutDialog>

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE
int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setApplicationName("Deepin-Kwin settings");
    DAboutDialog dialog;
    a.setProductName("Deepin-Kwin settings");
    dialog.setWebsiteLink("https://github.com/SiamSami/Deepin-kwin-settings");
    dialog.setCompanyLogo(QPixmap(""));
    dialog.setLicense("Licensed under GNU GPL 3");
    dialog.setVersion("Version 1.0 (Beta)");
    dialog.setProductName("Deepin-Kwin settings");
    dialog.setWebsiteName("Made by Siam Sami");
    dialog.setAcknowledgementVisible(false);
    a.setAboutDialog(&dialog);
    a.setStyle("dlight");
    deepin_kwin_settings w;
    w.setWindowTitle("Deepin-Kwin settings");
    w.show();

    return a.exec();
}
