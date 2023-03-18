/*
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
    [[nodiscard]] const QVector<Bot*>& enemies() const;
signals:
    void boardChanged();
    void levelChanged(unsigned id);
    void enemyScoreChanged(char objectId, unsigned score);
    void enemiesSpawned();
public slots:
    void onKeyPressed(KeyEvent key);
    void onTick();
    void onBotTick();
private:
    using script = char (*)(
        unsigned row, unsigned column, unsigned level,
        unsigned rows, unsigned columns, const char* objects
    );

    void processPlayerScript();
    void checkPlayerScore();
    void processEnemies();
    void processKeyPress(KeyEvent key, Bot* bot);
    void loadGameData() EXCEPT;
    [[nodiscard]] const GameLevel* currentLevel() const EXCEPT;
    [[nodiscard]] GameBoard* makeBoard(const GameLevel* level);
    void initializePlayer();
    void generateCoordsForEnemies();
    void spawnEnemies();
    static unsigned randUint(unsigned topBound);
    void loadScriptLib() EXCEPT;

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
    void* mScriptHandle;
    script mScript;
};
