#ifndef DOTS_H
#define DOTS_H

#include <QString>
#include <QMetaEnum>
#include <QDirIterator>
#include <QVector>
#include <QDir>

typedef struct TDot {
    int id;
    QString name;
    QString path;
} Dot;

template<typename type = TDot>
QList<type> *load_icons(void) {
    QList<type> *dots = new QList<type>();

    QDir dir(":/dots/");
    dir.setSorting(QDir::SortFlag::Name);
    QDirIterator it(dir);

    int index = 0;
    while (it.hasNext()) {
        QString tmp = it.next();
        dots->append({index, tmp, tmp});
        index++;
    }

    return dots;
}

// parser enum to string
template<typename QEnum>
QString qtEnumToString (const QEnum value) {
  return QString(QMetaEnum::fromType<QEnum>().valueToKey(value));
}

typedef struct TOptions {
    float width;
    float height;
    float size;
    QString dot;
} Options;

#endif // DOTS_H