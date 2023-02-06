
#include <QException>
#include "GameBoard.hpp"

GameBoard::GameBoard(QObject* parent, unsigned int rows, unsigned int columns, QVector<char>&& data) :
    QObject(parent), mRows(rows), mColumns(columns), mObjects(data)
{

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
