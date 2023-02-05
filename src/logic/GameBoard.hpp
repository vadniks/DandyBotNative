
#pragma once

#include <QObject>

class GameBoard : QObject {
public:
    explicit GameBoard(QObject* parent);
    ~GameBoard() override = default;
};
