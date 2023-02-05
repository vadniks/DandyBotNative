
#include "GameBoard.hpp"

GameBoard::GameBoard(QObject* parent) : QObject(parent), data(this), currentLevel(nullptr) {
    currentLevel = data.levels[0];
}
