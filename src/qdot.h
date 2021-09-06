#ifndef QDOT_H
#define QDOT_H

#include <memory>
#include <QDesktopWidget>
#include <QColorDialog>
#include <QMainWindow>
#include <QSettings>
#include <QMetaEnum>
#include <QList>
#include <QDirIterator>

#include "crosshair.h"
#include "dots.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QDot; }
QT_END_NAMESPACE

class QDot : public QMainWindow
{
    Q_OBJECT

public:
    QDot(QWidget *parent = nullptr);
    ~QDot();

    void set_default_options();
    QPixmap *init_dot();
    void load_settings(Options *options);
    void load_label(QLabel *label, QDesktopWidget *desktop);
    void show_crosshair();
    Crosshair *get_crosshair();

private slots:
    void changeEvent(QEvent *event);
    void on_default_settings_clicked();
    void on_set_clicked();

private:
    void set_settings(Options *options);
    Ui::QDot *ui;
    QSettings *settings;
    QWidget *screen;
    Options *options;
    QLabel *label;
    QList<TDot> *dots;
    QDesktopWidget *desktop;
    Crosshair *crosshair;
};
#endif // QDOT_H
