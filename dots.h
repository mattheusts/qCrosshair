#ifndef DOTS_H
#define DOTS_H

#include <QString>
#include <QMetaEnum>

enum DOT {
    blue_default,
    blue_default_dot,
    blue_dot,
    blue_ring,
    cod_crosshair,
    green_default,
    green_default_dot,
    green_dot,
    green_ring,
    hitmarker_crosshair,
    lightblue_default,
    lightblue_default_dot,
    lightblue_dot,
    lightblue_ring,
    pink_dot,
    pink_ring,
    red_default,
    red_default_dot,
    red_defaultlarge,
    red_defaultlarge_dot,
    red_dot,
    red_ring,
    white,
    white_default,
    white_default_dot,
    yellow_dot,
    yellow_ring
};

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
