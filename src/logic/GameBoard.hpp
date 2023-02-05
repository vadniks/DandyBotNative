
#pragma once

#include <QObject>
#include "GameData.hpp"

class GameBoard : public QObject {
    Q_OBJECT
public:
    explicit GameBoard(QObject* parent);

    const GameData data;
    const GameLevel* currentLevel;
};
