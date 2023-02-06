
#include <QException>
#include "GameBoard.hpp"

GameBoard::GameBoard(QObject* parent, unsigned int rows, unsigned int columns, QVector<char>&& objects) EXCEPT :
    QObject(parent), mRows(rows), mColumns(columns), mObjects(objects)
{
    if (rows * columns != objects.size()) throw QException();
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

void GameBoard::move(unsigned int fromRow, unsigned int fromColumn, unsigned int toRow, unsigned int toColumn) EXCEPT {
    setAt(objectAt(fromRow, fromColumn), toRow, toColumn);
    setAt(Objects::EMPTY, fromRow, fromColumn);
}
