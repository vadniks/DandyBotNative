
#include "Player.hpp"

Player::Player(QObject* parent, unsigned int row, unsigned int column) :
    QObject(parent), row(row), column(column), mCurrentScore(0), mTotalScore(0)
{}

unsigned Player::currentScore() const { return mCurrentScore; }

unsigned Player::totalScore() const { return mTotalScore; }

void Player::setCurrentScore(unsigned currentScore) {
    mCurrentScore = currentScore;
    mTotalScore += currentScore;
    emit scoreUpdated();
}
