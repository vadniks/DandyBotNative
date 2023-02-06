
#include <QVector>
#include "GameAlgorithm.hpp"

GameAlgorithm::GameAlgorithm(QObject* parent) : QObject(parent), mBoard(nullptr) {
    QVector<char> objects;
    objects.fill('#', 24 * 42);
    setBoard(new GameBoard(this, 24, 42, static_cast<decltype(objects)&&>(objects)));
}

GameAlgorithm::~GameAlgorithm() { delete mBoard; }

GameBoard* GameAlgorithm::board() const { return mBoard; }

void GameAlgorithm::setBoard(GameBoard* board) {
    delete mBoard;
    mBoard = board;
    emit boardChanged();
}
