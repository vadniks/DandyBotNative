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
#include <QQueue>
#include "GameBoard.hpp"
#include "GameLevel.hpp"
#include "../util.hpp"
#include "../KeyEvent.hpp"
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
    void onKeyPressed(KeyEvent key);
    void onPlayerScoreUpdated();
    void onTick();
    void onBotTick();
private:
    void processEnemies();
    void processKeyPress(KeyEvent key, Bot* bot);
    void loadGameData() EXCEPT;
    [[nodiscard]] const GameLevel* currentLevel() const EXCEPT;
    [[nodiscard]] GameBoard* makeBoard(const GameLevel* level);
    void initializePlayer();
    void generateCoordsForEnemies();
    void spawnEnemies();
    static unsigned randUint(unsigned topBound);

    GameBoard* mBoard;
    QVector<const GameLevel*> mLevels;
    QMap<char, QIcon> mObjectDescriptions;
    Bot* mPlayer;
    unsigned mCurrentLevelId;
    bool mHasWon;
    QTimer mTimer;
    QVector<Bot*> mEnemies;
    QVector<QPair<unsigned, unsigned>> mCurrentFreeCoords;
    QQueue<KeyEvent> mKeyEvents;
};
