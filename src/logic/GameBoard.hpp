
#pragma once

#include <QObject>

class GameBoard : public QObject {
    Q_OBJECT
public:
    explicit GameBoard(QObject* parent, unsigned rows, unsigned columns);

    const unsigned mRows;
    const unsigned mColumns;
};
