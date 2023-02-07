/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

#pragma once

#include <QObject>
#include "../util.hpp"

class Player final : public QObject {
    Q_OBJECT
public:
    Player(QObject* parent, unsigned row, unsigned column);

    [[nodiscard]] unsigned currentScore() const;
    [[nodiscard]] unsigned totalScore() const;
    void setCurrentScore(unsigned currentScore);
    void updateCurrentScore(unsigned delta, bool increment) EXCEPT;

    unsigned row;
    unsigned column;
signals:
    void scoreUpdated();
private:
    unsigned mCurrentScore;
    unsigned mTotalScore;
};
