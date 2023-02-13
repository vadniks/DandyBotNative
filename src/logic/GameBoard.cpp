/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 */

/*
 * GNU GPL v2
 *
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

#include "GameBoard.hpp"
#include "../Exception.hpp"
#include "../consts.hpp"

GameBoard::GameBoard(QObject* parent, unsigned rows, unsigned columns, QVector<char>&& objects) EXCEPT :
    QObject(parent), mRows(rows), mColumns(columns), mObjects(static_cast<decltype(objects)&&>(objects))
{ setSize(rows, columns); }

const QVector<char>& GameBoard::objects() const { return mObjects; }

char GameBoard::objectAt(unsigned row, unsigned column) const EXCEPT {
    if (row >= mRows or column >= mColumns) throw Exception("out of bounds");
    return mObjects.at(row * mColumns + column);
}

void GameBoard::setAt(char object, unsigned row, unsigned column) EXCEPT {
    if (row >= mRows or column >= mColumns) throw Exception("out of bounds");
    mObjects[row * mColumns + column] = object;
    emit boardUpdated();
}

void GameBoard::move(unsigned fromRow, unsigned fromColumn, unsigned toRow, unsigned toColumn) EXCEPT {
    const auto object = objectAt(fromRow, fromColumn);

    if (object != PLAYER_OBJ and (object < ENEMY_MIN_OBJ or object > ENEMY_MAX_OBJ))
        throw Exception("only player and enemies are allowed to be moved");

    setAt(object, toRow, toColumn);
    setAt(EMPTY_OBJ, fromRow, fromColumn);
}

unsigned GameBoard::rows() const { return mRows; }

unsigned GameBoard::columns() const { return mColumns; }

void GameBoard::setSize(unsigned rows, unsigned columns) EXCEPT {
    if (columns * GAME_OBJECT_SIZE > APP_WIDTH
        or rows * GAME_OBJECT_SIZE > APP_HEIGHT
        or rows * columns != mObjects.size()) throw Exception("board size exceeds app's window size");
    mRows = rows;
    mColumns = columns;
    emit boardUpdated();
}
