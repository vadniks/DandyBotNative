
#include <QException>
#include "GameBoard.hpp"
#include "../consts.hpp"

GameBoard::GameBoard(QObject* parent, unsigned rows, unsigned columns, QVector<char>&& objects) EXCEPT :
    QObject(parent), mRows(rows), mColumns(columns), mObjects(static_cast<decltype(objects)&&>(objects))
{
    setSize(rows, columns);
}

const QVector<char>& GameBoard::objects() const { return mObjects; }

char GameBoard::objectAt(unsigned row, unsigned column) const EXCEPT {
    if (row >= mRows or column >= mColumns) throw QException();
    return mObjects.at(row * mColumns + column);
}

void GameBoard::setAt(char object, unsigned row, unsigned column) EXCEPT {
    if (row >= mRows or column >= mColumns) throw QException();
    mObjects[row * mColumns + column] = object;
    emit boardUpdated();
}

void GameBoard::move(unsigned fromRow, unsigned fromColumn, unsigned toRow, unsigned toColumn) EXCEPT {
    setAt(objectAt(fromRow, fromColumn), toRow, toColumn);
    setAt(EMPTY_OBJ, fromRow, fromColumn);
}

unsigned GameBoard::rows() const { return mRows; }

unsigned GameBoard::columns() const { return mColumns; }

void GameBoard::setSize(unsigned rows, unsigned columns) EXCEPT {
    if (columns * GAME_OBJECT_SIZE > APP_WIDTH
        or rows * GAME_OBJECT_SIZE > APP_HEIGHT
        or rows * columns != mObjects.size()) throw QException();
    mRows = rows;
    mColumns = columns;
    emit boardUpdated();
}
