/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 */

/*
 * GNU GPL v2
 *
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

#pragma ide diagnostic ignored "cert-msc51-cpp"
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QIcon>
#include <QMessageBox>
#include <QApplication>
#include <ctime>
#include <cstdlib>
#include "GameAlgorithm.hpp"
#include "../Exception.hpp"
#include "../consts.hpp"

GameAlgorithm::GameAlgorithm(QObject* parent)
    : QObject(parent), mBoard(nullptr), mPlayer(nullptr), mCurrentLevelId(0), mHasWon(false), mTimer(this)
{
    mObjectDescriptions[EMPTY_OBJ] = QIcon(EMPTY_ICON);
    mObjectDescriptions[BLOC_OBJ] = QIcon(BLOC_ICON);
    for (char i = COIN_MIN_OBJ; i <= COIN_MAX_OBJ; i++)
        mObjectDescriptions[i] = QIcon(COIN_ICON);
    for (char i = ENEMY_MIN_OBJ; i <= ENEMY_MAX_OBJ; i++)
        mObjectDescriptions[i] = QIcon(QString::asprintf("%s%c%s", ENEMY_ICON_PREFIX, i, ICON_SUFFIX));
    mObjectDescriptions[PLAYER_OBJ] = QIcon(PLAYER_ICON);

    loadGameData();
    setBoard(makeBoard(currentLevel()));

    mPlayer = new Bot(this, 0, 0, PLAYER_OBJ);
    initializePlayer();

    srand(time(nullptr));
    spawnEnemies();

    connect(&mTimer, &QTimer::timeout, this, &GameAlgorithm::onTick);
    mTimer.setSingleShot(false);
    mTimer.setInterval(static_cast<signed>(TICK_INTERVAL));
    mTimer.start();
}

GameAlgorithm::~GameAlgorithm() {
    delete mBoard;
    for (const GameLevel* item : mLevels) delete item;
    delete mPlayer;
    for (const Bot* item : mEnemies) delete item;
}

GameBoard* GameAlgorithm::board() const { return mBoard; }

void GameAlgorithm::setBoard(GameBoard* board) {
    delete mBoard;
    mBoard = board;
    emit boardChanged();
}

const QMap<char, QIcon>& GameAlgorithm::objectDescriptions() { return mObjectDescriptions; }

const Bot* GameAlgorithm::player() const { return mPlayer; }

const QVector<Bot*>& GameAlgorithm::enemies() const { return mEnemies; }

void GameAlgorithm::onKeyPressed(KeyEvent key) { mKeyEvents.enqueue(key); }

void GameAlgorithm::onTick() {
    if (!mKeyEvents.isEmpty())
        processKeyPress(mKeyEvents.dequeue(), mPlayer);

    const auto chance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    if (chance <= BOT_MOVE_CHANCE) onBotTick();

    checkPlayerScore();
}

void GameAlgorithm::onBotTick() { processEnemies(); }

void GameAlgorithm::checkPlayerScore() {
    if (mPlayer->currentScore() <
        static_cast<unsigned>(floorf(static_cast<float>(currentLevel()->steps) * PLAYER_SCORE_TO_WIN_MULTIPLIER)))
        return;

    if (mCurrentLevelId == mLevels.size() - 1) {
        mHasWon = true;

        QMessageBox box(dynamic_cast<QWidget*>(parent()));
        box.setModal(true);
        box.setText(YOU_WON);
        box.exec();

        QApplication::quit();
    } else {
        mCurrentLevelId++;
        setBoard(makeBoard(currentLevel()));
        mPlayer->setCurrentScore(0);
        initializePlayer();
        emit levelChanged(mCurrentLevelId);
        spawnEnemies();
    }
}

void GameAlgorithm::processEnemies() {
    for (Bot* enemy : mEnemies) {
        KeyEvent key;
        switch (randUint(4)) {
            case 0: key = KeyEvent::W; break;
            case 1: key = KeyEvent::A; break;
            case 2: key = KeyEvent::S; break;
            case 3: key = KeyEvent::D; break;
        }
        processKeyPress(key, enemy);
    }
}

void GameAlgorithm::processKeyPress(KeyEvent key, Bot* bot) {
    if (mHasWon) return;

    unsigned newRow = bot->currentRow,
        newColumn = bot->currentColumn,
        rows = mBoard->rows(),
        columns = mBoard->columns();
    char object = 0;

    const auto isBlockOrBot = [&](){
        const char object = mBoard->objectAt(newRow, newColumn);
        return object == BLOC_OBJ
            or (object >= ENEMY_MIN_OBJ and object <= ENEMY_MAX_OBJ)
            or object == PLAYER_OBJ;
    };

    const auto setObject = [&](){ object = mBoard->objectAt(newRow, newColumn); };

    const auto checkNHandleCoin = [&](){
        if (object >= COIN_MIN_OBJ and object <= COIN_MAX_OBJ)
            bot->incrementCurrentScore(object - COIN_MIN_OBJ + 1);
    };

    const auto isEnemyNearCoin = [&](){
        const char object = mBoard->objectAt(newRow, newColumn);
        return bot->objectId >= ENEMY_MIN_OBJ and bot->objectId <= ENEMY_MAX_OBJ
            and object >= COIN_MIN_OBJ and object <= COIN_MAX_OBJ;
    };

    const bool canTakeCoin = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) < BOT_COIN_TAKE_CHANCE;
    switch (key) {
        case KeyEvent::W:
            if ((newRow = bot->currentRow - 1) >= rows) break;
            if (isBlockOrBot()) break;

            setObject();

            if (!isEnemyNearCoin() or canTakeCoin) {
                mBoard->move(bot->currentRow, bot->currentColumn, newRow, newColumn);
                bot->currentRow = newRow;
                checkNHandleCoin();
            }

            emit boardChanged();
            break;
        case KeyEvent::A:
            if ((newColumn = bot->currentColumn - 1) >= columns) break;
            if (isBlockOrBot()) break;

            setObject();

            if (!isEnemyNearCoin() or canTakeCoin) {
                mBoard->move(bot->currentRow, bot->currentColumn, newRow, newColumn);
                bot->currentColumn = newColumn;
                checkNHandleCoin();
            }

            emit boardChanged();
            break;
        case KeyEvent::S:
            if ((newRow = bot->currentRow + 1) >= rows) break;
            if (isBlockOrBot()) break;

            setObject();

            if (!isEnemyNearCoin() or canTakeCoin) {
                mBoard->move(bot->currentRow, bot->currentColumn, newRow, newColumn);
                bot->currentRow = newRow;
                checkNHandleCoin();
            }

            emit boardChanged();
            break;
        case KeyEvent::D:
            if ((newColumn = bot->currentColumn + 1) >= columns) break;
            if (isBlockOrBot()) break;

            setObject();

            if (!isEnemyNearCoin() or canTakeCoin) {
                mBoard->move(bot->currentRow, bot->currentColumn, newRow, newColumn);
                bot->currentColumn = newColumn;
                checkNHandleCoin();
            }

            emit boardChanged();
            break;
    }
}

void GameAlgorithm::loadGameData() EXCEPT {
    auto file = QFile(GAME_DATA);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    auto document = QJsonDocument::fromJson(file.readAll());
    auto json = document.object();
    auto levelsArray = json[LEVELS].toArray();
    auto mapsArray = json[MAPS].toArray();

    const unsigned size = levelsArray.size();
    if (size != mapsArray.size()) throw Exception("amount of levels is greater or less than amount of maps");

    for (unsigned i = 0; i < size; i++) {
        auto level = levelsArray[i].toObject();
        auto position = level[START].toArray();
        QVector<char> map;
        unsigned rows = 0, columns = 0, coins = 0;

        for (const QJsonValueRef& item : mapsArray[i].toArray()) {
            const auto string = item.toString();
            unsigned stringSize = 0;

            for (const QChar& qChar : string) {
                const char chr = qChar.toLatin1();

                if (!mObjectDescriptions.contains(chr))
                    throw Exception("map contains unknown character");

                if (chr >= COIN_MIN_OBJ and chr <= COIN_MAX_OBJ)
                    coins++;

                map.push_back(chr);
                stringSize++;
            }
            rows++;

            if (columns != 0 and columns != stringSize) throw Exception("currentRow sizes must be same");
            columns = stringSize;
        }

        const unsigned steps = level[STEPS].toInt();
        if (coins < steps) throw Exception("amount of steps must not be greater than amount of coin objects on the map");

        const int bots = level[BOTS].toInt();
        if (bots < 0 or bots > ENEMY_MAX_OBJ - ENEMY_MIN_OBJ)
            throw Exception("amount of bots must be (equal to 0 or greater) and less than 6 or equal");

        mLevels.push_back(new GameLevel(
            this,
            static_cast<unsigned>(level[MAP].toInt()),
            GameLevel::Position(
                static_cast<unsigned>(position[0].toInt()),
                static_cast<unsigned>(position[1].toInt())
            ),
            static_cast<unsigned>(coins),
            static_cast<QVector<char>&&>(map),
            rows,
            columns,
            bots
        ));
    }

    file.close();
}

const GameLevel* GameAlgorithm::currentLevel() const EXCEPT {
    if (mCurrentLevelId >= mLevels.size()) throw Exception("currentLevelId exceeds levels' size");
    return mLevels[mCurrentLevelId];
}

GameBoard* GameAlgorithm::makeBoard(const GameLevel* level)
{ return new GameBoard(this, level->rows, level->columns, QVector<char>(level->map)); }

void GameAlgorithm::initializePlayer() {
    const auto level = currentLevel();
    unsigned row = level->start.second, column = level->start.first;

    mPlayer->currentRow = row;
    mPlayer->currentColumn = column;
    mBoard->setAt(PLAYER_OBJ, row, column);
}

void GameAlgorithm::generateCoordsForEnemies() {
    const unsigned rows = mBoard->rows(), columns = mBoard->columns();
    const auto startPos = currentLevel()->start;

    for (unsigned row = 0; row < rows; row++)
        for (unsigned column = 0; column < columns; column++) {
            const char object = mBoard->objectAt(row, column);

            if (object != BLOC_OBJ and (object < COIN_MIN_OBJ or object > COIN_MAX_OBJ)
                and row != startPos.second and column != startPos.first)
                mCurrentFreeCoords.push_back({ row, column });
        }
}

void GameAlgorithm::spawnEnemies() {
    for (const Bot* enemy : mEnemies)
        delete enemy;
    mEnemies.clear();

    mCurrentFreeCoords.clear();
    generateCoordsForEnemies();
    const auto totalEnemies = static_cast<char>(currentLevel()->enemies);

    QVector<QPair<unsigned, unsigned>> usedPositions;

    for (char chr = ENEMY_MIN_OBJ, enemies = 0; chr <= ENEMY_MAX_OBJ and enemies < totalEnemies; chr++, enemies++) {
        QPair<unsigned, unsigned> position;

        do { position = mCurrentFreeCoords[randUint(mCurrentFreeCoords.size() - 1)]; }
        while (usedPositions.contains(position));

        usedPositions.push_back(position);

        auto bot = new Bot(this, position.first, position.second, chr);
        connect(bot, &Bot::scoreUpdated, this, [this, bot](){ emit enemyScoreChanged(bot->objectId, bot->totalScore()); });
        mEnemies.push_back(bot);
        mBoard->setAt(chr, position.first, position.second);
    }
    emit enemiesSpawned();
}

unsigned GameAlgorithm::randUint(unsigned topBound) { return rand() / (RAND_MAX / topBound); }
