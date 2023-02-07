
#pragma once

#include <QObject>

class Player final : public QObject {
    Q_OBJECT
public:
    Player(QObject* parent, unsigned row, unsigned column);

    [[nodiscard]] unsigned currentScore() const;
    [[nodiscard]] unsigned totalScore() const;
    void setCurrentScore(unsigned currentScore);

    unsigned row;
    unsigned column;
signals:
    void scoreUpdated();
private:
    unsigned mCurrentScore;
    unsigned mTotalScore;
};
