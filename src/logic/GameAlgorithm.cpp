
#include "GameAlgorithm.hpp"

GameAlgorithm::GameAlgorithm(QObject* parent) : QObject(parent), mBoard(nullptr) {

}

GameAlgorithm::~GameAlgorithm() { delete mBoard; }

GameBoard* GameAlgorithm::board() const { return mBoard; }

void GameAlgorithm::setBoard(GameBoard* board) {
    if (mBoard != nullptr) delete mBoard;
    mBoard = board;
    emit boardChanged();
}
