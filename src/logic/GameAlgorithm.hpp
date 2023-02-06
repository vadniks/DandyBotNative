
#pragma once

#include <QObject>
#include "GameBoard.hpp"

class GameAlgorithm : public QObject {
    Q_OBJECT
public:
    explicit GameAlgorithm(QObject* parent);
    ~GameAlgorithm() override;
    [[nodiscard]] GameBoard* board() const;
    void setBoard(GameBoard* board);
signals:
    void boardChanged();
private:
    GameBoard* mBoard;
};
