#include "qdot.h"
#include "ui_qdot.h"

QDot::QDot(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QDot)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(250, 200));

//    Show minimized window
//    setWindowFlags(Qt::WindowMinimizeButtonHint);
//    this->setWindowState(Qt::WindowMinimized);

    screen = QApplication::desktop()->screen();
    settings = new QSettings("QDot", QSettings::IniFormat);

//     load saved options
    options = new Options();
    this->load_settings(options);

//    List all crosshair in comboBox
    dots = load_icons();
    for (auto d: *dots) {
        this->ui->comboBoxIcons->addItem(QIcon(d.path), "");
        if (d.path == options->dot)
            this->ui->comboBoxIcons->setCurrentIndex(d.id);
    }

    if (options->width == 0 && options->height == 0) {
        this->set_default_options();
        this->load_settings(options);
    }

    ui->width->setText(QString::number(options->width));
    ui->height->setText(QString::number(options->height));
    ui->size->setText(QString::number(options->size));
}


QDot::~QDot()
{
    delete settings;
    delete screen;
    delete options;
    delete desktop;
    delete label;
    delete dots;
    delete ui;
}

void QDot::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange) {
        if (this->isMinimized()) {
            hide();
        }
    }
}

void QDot::set_default_options() {
    const float width = this->screen->width() / 2;
    const float height = this->screen->height() / 2;
    const int size = 20;
    QString dot = ":/dots/blue_default.png";

    ui->width->setText(QString::number(width));
    ui->height->setText(QString::number(height));
    ui->size->setText(QString::number(size));
    ui->comboBoxIcons->setCurrentIndex(0);

    options->height = height;
    options->width = width;
    options->size = size;
    options->dot = dot;

    set_settings(options);

    emit crosshair.operator*()->update();
}


void QDot::load_settings(Options *options) {
    const float width = this->settings->value("width").value<float>();
    const float height = this->settings->value("height").value<float>();
    const int size = this->settings->value("size").value<float>();
    const QString dot = this->settings->value("dot").value<QString>();

    options->width = width;
    options->height = height;
    options->size = size;
    options->dot = dot;
}

void QDot::set_settings(Options *options) {
    settings->setValue("width", options->width);
    settings->setValue("height", options->height);
    settings->setValue("size", options->size);
    settings->setValue("dot", options->dot);
}

void QDot::on_default_settings_clicked() {
    set_default_options();
}

QPixmap *QDot::init_dot() {
    return new QPixmap();
}

void QDot::load_label(QLabel *label, QDesktopWidget *desktop) {
    this->label = label;
    this->desktop = desktop;

    crosshair = std::make_shared<Crosshair *>(new Crosshair(label, desktop));
}

void QDot::show_crosshair() {
    this->crosshair.operator*()->render_crosshair_dot(options);
}

std::shared_ptr<Crosshair *> QDot::get_crosshair() {
    return this->crosshair;
}

void QDot::on_set_clicked() {
    options->height = ui->height->text().toFloat();
    options->width = ui->width->text().toFloat();
    options->size = ui->size->text().toInt();

    const int index =  ui->comboBoxIcons->currentIndex();
    TDot dot = dots->at(index);
    options->dot = dot.path;

    set_settings(options);
    emit crosshair.operator*()->update();
}
