/*
 * Copyright (c) 2021 Peter Sovietov (https://github.com/true-grue)
 *
 * Copyright (C) 2023 Vad Nik (https://github.com/vadniks)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
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
        unsigned columns,
        unsigned enemies
    ) :
        QObject(parent),
        id(id),
        start(static_cast<Position&&>(start)),
        steps(steps),
        map(static_cast<QVector<char>&&>(map)),
        rows(rows),
        columns(columns),
        enemies(enemies)
    {};

    [[maybe_unused]] const unsigned id;
    const Position start; // column (x), row (y)
    const unsigned steps;
    const QVector<char> map;
    const unsigned rows;
    const unsigned columns;
    const unsigned enemies;
};
