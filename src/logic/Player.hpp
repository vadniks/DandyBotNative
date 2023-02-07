
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
