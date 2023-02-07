
#pragma once

#include <QObject>

class Player final : public QObject {
    Q_OBJECT
public:
    Player(QObject* parent, unsigned row, unsigned column)
    : QObject(parent), row(row), column(column), currentScore(0), totalScore(0) {};

    unsigned row;
    unsigned column;
    unsigned currentScore;
    unsigned totalScore;
};
