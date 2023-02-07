
#pragma once

#include <QObject>
#include <QPair>
#include <QVector>

class GameLevel : public QObject {
    Q_OBJECT
public:
    using Position = QPair<unsigned, unsigned>;
    GameLevel(
        QObject* parent,
        unsigned id,
        Position&& start,
        unsigned steps,
        QVector<char>&& map,
        unsigned rows,
        unsigned columns
    ) :
        QObject(parent),
        id(id),
        start(static_cast<Position&&>(start)),
        steps(steps),
        map(static_cast<QVector<char>&&>(map)),
        rows(rows),
        columns(columns)
    {};

    const unsigned id;
    const Position start;
    const unsigned steps;
    const QVector<char> map;
    const unsigned rows;
    const unsigned columns;
};
