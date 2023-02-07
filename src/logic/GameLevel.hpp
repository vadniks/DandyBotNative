/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

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
