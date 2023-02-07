/*
 * Inspired by the work of Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
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
