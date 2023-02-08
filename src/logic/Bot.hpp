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
protected:
    unsigned mCurrentScore;
    unsigned mTotalScore;
};
