
#include "GameAlgorithm.hpp"

GameAlgorithm::GameAlgorithm(QObject* parent) : QObject(parent), mBoard(nullptr) {
    mBoard = new GameBoard(this, 5, 5, {
        '#', '#', '#', '#', '#',
        '#', '#', '#', '#', '#',
        '#', '#', '#', '#', '#',
        '#', '#', '#', '#', '#',
        '#', '#', '#', '#', '#'
    });
}

GameAlgorithm::~GameAlgorithm() { delete mBoard; }

GameBoard* GameAlgorithm::board() const { return mBoard; }

void GameAlgorithm::setBoard(GameBoard* board) {
    if (mBoard != nullptr) delete mBoard;
    mBoard = board;
    emit boardChanged();
}
