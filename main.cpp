#include <DApplication>
#include <zconf.h>
#include <QtWidgets/QSystemTrayIcon>
#include "mainwindow.h"


DWIDGET_USE_NAMESPACE

int main(int argc, char **argv) {
    DApplication::loadDXcbPlugin();
    DApplication app(argc, argv);
    if (app.setSingleInstance(QString("flyos-clipboard_%1").arg(getuid()))) {
        app.setTheme("light");
        app.loadTranslator();
        app.setApplicationDisplayName("剪切板");
        app.setApplicationName("flyos-clipboard");
        app.setApplicationVersion("0.0.2");
        app.setOrganizationName("flyos");
        app.setOrganizationDomain("fly-os.xyz");
//        app.setApplicationDescription(DApplication::translate("MainWindow", "FlyOS剪切板") + "\n");
//        app.setProductIcon(QPixmap(":/images/logo.png"));
        app.setWindowIcon(QIcon(":/images/logo.png"));

        app.setProperty("productName", "飞龙剪切板");
        app.setProperty("version", "0.0.2");
        app.setProperty("description", "飞龙剪切板是一款记录剪切板历史的软件");
        app.setProperty("productrtIcon", ":/images/logo.png");

        mainwindow window;
        return app.exec();
    }

    return 0;
}