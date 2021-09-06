#include "src/qdot.h"
#include <Windows.h>
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QStyle>
#include <QDesktopWidget>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QPainter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    QDot qdot;
    // Open settings start window
    //    qdot.show();

    if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole())

    a.setApplicationDisplayName("QDot");
    a.setApplicationName("QDotApp");
    a.setOrganizationName("QDot");
    a.setApplicationVersion("0.0.1");
    a.setWindowIcon(QIcon(":/icon/QDot.ico"));

    // Try icon
    QSystemTrayIcon *iconTray = new QSystemTrayIcon(QIcon(":/icon/QDot.ico"));
    iconTray->show();

    auto *quit = new QAction("&Quit", qApp);
    auto *settings = new QAction("&Settings");

    // Close QDot
    qApp->connect(quit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    // Open settings
    qApp->connect(settings, SIGNAL(triggered()), &qdot, SLOT(show()));

    QMenu *tryMenu = new QMenu(qApp->desktop());
    tryMenu->addAction(settings);
    tryMenu->addSeparator();
    tryMenu->addAction(quit);

    iconTray->setContextMenu(tryMenu);
    iconTray->showMessage(QString("QDot"), "Welcome to QDot, to configure it just click with the right mouse button on the icon.", QSystemTrayIcon::Information);

    iconTray->show();

    QDesktopWidget *desktop = qApp->desktop();
    QLabel *label = new QLabel(qApp->desktop());

    qdot.load_label(label, desktop);
    qdot.show_crosshair();

    Crosshair *crosshair = qdot.get_crosshair();

    qApp->connect(crosshair, &Crosshair::update, label, [&](){
        qdot.show_crosshair();
    });

    return a.exec();
}
