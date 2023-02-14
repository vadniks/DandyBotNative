/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 */

/*
 * GNU GPL v2
 *
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

#pragma once

#include <QObject>
#include "../util.hpp"

class Bot final : public QObject {
    Q_OBJECT
public:
    Bot(QObject* parent, unsigned row, unsigned column, char objectId) EXCEPT;

    [[nodiscard]] unsigned currentScore() const;
    [[nodiscard]] unsigned totalScore() const;
    void setCurrentScore(unsigned currentScore);
    void incrementCurrentScore(unsigned delta);

    unsigned currentRow;
    unsigned currentColumn;
    const char objectId;
signals:
    void scoreUpdated();
private:
    unsigned mCurrentScore;
    unsigned mTotalScore;
};
