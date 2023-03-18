/*
 * Copyright (c) 2021 Peter Sovietov (https://github.com/true-grue)
 *
 * Copyright (C) 2023 Vad Nik (https://github.com/vadniks)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
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
