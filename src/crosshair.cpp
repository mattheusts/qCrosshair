#include "crosshair.h"


Crosshair::Crosshair(QLabel *label, QDesktopWidget *desktop) {
    this->label = label;
    this->desktop = desktop;
}

Crosshair::~Crosshair() {
    delete label;
}

void Crosshair::render_crosshair_dot(Options *options) {
    // represents the monitor screen, if there are more monitors it will have to be modified
    int screenNumber = 0;

    QPixmap *pixmap = new QPixmap();
    pixmap->load(options->dot);

    int x, y;
    QRect rectScreen;
    rectScreen = desktop->screenGeometry(screenNumber);

    x = rectScreen.x() + options->width - options->size / 2 ;
    y = rectScreen.y() + options->height - options->size / 2 ;

    label->setAttribute(Qt::WA_TranslucentBackground);
    label->setAttribute(Qt::WA_TransparentForMouseEvents);
    label->setPixmap(pixmap->scaled(options->size, options->size));
    label->setGeometry( x, y, options->size, options->size );
    label->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::SubWindow);
    label->show();
}
