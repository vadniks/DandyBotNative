
#pragma once

#include <QObject>
#include "GameBoard.hpp"
#include "GameLevel.hpp"
#include "../util.hpp"

class GameAlgorithm final : public QObject {
    Q_OBJECT
public:
    explicit GameAlgorithm(QObject* parent);
    ~GameAlgorithm() override;
    [[nodiscard]] GameBoard* board() const;
    void setBoard(GameBoard* board);
    const QMap<char, QIcon>& objectDescriptions();
signals:
    void boardChanged();
private:
    void loadGameData() EXCEPT;

    GameBoard* mBoard;
    QVector<const GameLevel*> mLevels;
    QMap<char, QIcon> mObjectDescriptions;
};
