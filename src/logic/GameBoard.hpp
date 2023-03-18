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
#include <QVector>
#include <QMap>
#include <functional>
#include "../util.hpp"

class GameBoard final : public QObject {
    Q_OBJECT
public:
    explicit GameBoard(QObject* parent, unsigned rows, unsigned columns, QVector<char>&& objects) EXCEPT;
    [[nodiscard]] const QVector<char>& objects() const;
    [[nodiscard]] char objectAt(unsigned row, unsigned column) const EXCEPT;
    void setAt(char object, unsigned row, unsigned column) EXCEPT;
    void move(unsigned fromRow, unsigned fromColumn, unsigned toRow, unsigned toColumn) EXCEPT;
    [[nodiscard]] unsigned rows() const;
    [[nodiscard]] unsigned columns() const;
    void setSize(unsigned rows, unsigned columns) EXCEPT;
signals:
    void boardUpdated();
private:
    unsigned mRows;
    unsigned mColumns;
    QVector<char> mObjects;
};
