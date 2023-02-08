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
#include <QVector>
#include <QMap>
#include <QTimer>
#include "GameBoard.hpp"
#include "GameLevel.hpp"
#include "../util.hpp"
#include "../Keys.hpp"
#include "Bot.hpp"

class GameAlgorithm final : public QObject {
    Q_OBJECT
public:
    explicit GameAlgorithm(QObject* parent);
    ~GameAlgorithm() override;
    [[nodiscard]] GameBoard* board() const;
    void setBoard(GameBoard* board);
    const QMap<char, QIcon>& objectDescriptions();
    [[nodiscard]] const Bot* player() const;
signals:
    void boardChanged();
    void levelChanged(unsigned id);
public slots:
    void onKeyPressed(Keys key);
    void onPlayerScoreUpdated();
    void onTick();
private:
    void loadGameData() EXCEPT;
    [[nodiscard]] const GameLevel* currentLevel() const EXCEPT;
    [[nodiscard]] GameBoard* makeBoard(const GameLevel* level);
    void initializePlayer();
    void generateCoordsForEnemies();
    void spawnEnemies();

    GameBoard* mBoard;
    QVector<const GameLevel*> mLevels;
    QMap<char, QIcon> mObjectDescriptions;
    Bot* mPlayer;
    unsigned mCurrentLevelId;
    bool mHasWon;
    QTimer mTimer;
    QVector<Bot*> mEnemies;
    QVector<QPair<unsigned, unsigned>> mCurrentFreeCoords;
};
