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

    auto quit = std::make_unique<QAction *>(new QAction("&Quit", qApp));
    auto settings = std::make_unique<QAction *>(new QAction("&Settings"));

    // Close QDot
    qApp->connect(*quit.get(), SIGNAL(triggered()), qApp, SLOT(quit()));

    // Open settings
    qApp->connect(*settings.get(), SIGNAL(triggered()), &qdot, SLOT(show()));

    QMenu *tryMenu = new QMenu(qApp->desktop());
    tryMenu->addAction(*settings.get());
    tryMenu->addSeparator();
    tryMenu->addAction(*quit.get());

    iconTray->setContextMenu(tryMenu);
    iconTray->showMessage(QString("QDot"), "Welcome to QDot, to configure it just click with the right mouse button on the icon.", QSystemTrayIcon::Information);

    iconTray->show();

    auto desktop = std::make_shared<QDesktopWidget *>(qApp->desktop());
    auto label = std::make_shared<QLabel *>(new QLabel(qApp->desktop()));

    qdot.load_label(*label, *desktop);
    qdot.show_crosshair();

    std::shared_ptr<Crosshair *> crosshair = qdot.get_crosshair();

    qApp->connect(*crosshair, &Crosshair::update, *label, [&](){
        qdot.show_crosshair();
    });

    return a.exec();
}
