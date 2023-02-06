
#include <QVector>
#include "GameAlgorithm.hpp"

GameAlgorithm::GameAlgorithm(QObject* parent) : QObject(parent), mBoard(nullptr) {
    QVector<char> objects;
    objects.fill('#', 28 * 30);
    mBoard = new GameBoard(this, 28, 30, static_cast<decltype(objects)&&>(objects));
}

GameAlgorithm::~GameAlgorithm() { delete mBoard; }

GameBoard* GameAlgorithm::board() const { return mBoard; }

void GameAlgorithm::setBoard(GameBoard* board) {
    if (mBoard != nullptr) delete mBoard;
    mBoard = board;
    emit boardChanged();
}
