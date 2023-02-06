
#include "GameBoard.hpp"

GameBoard::GameBoard(QObject* parent, unsigned int rows, unsigned int columns) :
    QObject(parent), mRows(rows), mColumns(columns), mData(rows * columns)
{

}

const QVector<char>& GameBoard::data() const { return mData; }
