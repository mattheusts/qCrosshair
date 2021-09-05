#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <QDesktopWidget>
#include <QDebug>
#include <QLabel>

#include "dots.h"

class Crosshair : public QObject
{
    Q_OBJECT
public:
    Crosshair() = default;
    Crosshair(QLabel *label, QDesktopWidget *desktop);
    void render_crosshair_dot(Options *options);

    ~Crosshair();

private: signals:
    void update();

private:
    QLabel *label;
    QDesktopWidget *desktop;
};

#endif // CROSSHAIR_H
