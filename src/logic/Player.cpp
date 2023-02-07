/*
 * Inspired by the work of Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

#include "Player.hpp"
#include "../Exception.hpp"

Player::Player(QObject* parent, unsigned row, unsigned column) :
    QObject(parent), row(row), column(column), mCurrentScore(0), mTotalScore(0)
{}

unsigned Player::currentScore() const { return mCurrentScore; }

unsigned Player::totalScore() const { return mTotalScore; }

void Player::setCurrentScore(unsigned currentScore) {
    mCurrentScore = currentScore;
    mTotalScore += currentScore;
    emit scoreUpdated();
}

void Player::updateCurrentScore(unsigned delta, bool increment) EXCEPT {
    if (!increment and delta > mCurrentScore) throw Exception("decrementing delta must be less than current score");
    setCurrentScore(increment ? mCurrentScore + delta : mCurrentScore - delta);
}
