/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

#include "Bot.hpp"
#include "../consts.hpp"
#include "../Exception.hpp"

Bot::Bot(QObject* parent, unsigned row, unsigned column, char objectId) EXCEPT :
    QObject(parent),
    currentRow(row),
    currentColumn(column),
    objectId(objectId),
    mCurrentScore(0),
    mTotalScore(0)
{
    if (objectId != PLAYER_OBJ and
        (objectId < ENEMY_MIN_OBJ and objectId > ENEMY_MAX_OBJ)
    ) throw Exception("wrong object id");
}

unsigned Bot::currentScore() const { return mCurrentScore; }

unsigned Bot::totalScore() const { return mTotalScore; }

void Bot::setCurrentScore(unsigned currentScore) {
    mCurrentScore = currentScore;
    emit scoreUpdated();
}

void Bot::incrementCurrentScore(unsigned delta) {
    const unsigned score = mCurrentScore + delta;
    score > mTotalScore ? mTotalScore = score : mTotalScore += delta;
    setCurrentScore(score);
}
