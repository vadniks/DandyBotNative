
#pragma once

#include <QObject>
#include <QVector>
#include <QMap>
#include "GameBoard.hpp"
#include "GameLevel.hpp"
#include "../util.hpp"
#include "../Keys.hpp"
#include "Player.hpp"

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
public slots:
    void onKeyPressed(Keys key);
    void onPlayerScoreUpdated();
private:
    void loadGameData() EXCEPT;

    GameBoard* mBoard;
    QVector<const GameLevel*> mLevels;
    QMap<char, QIcon> mObjectDescriptions;
    Player* mPlayer;
};
