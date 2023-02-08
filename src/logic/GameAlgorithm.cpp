/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

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
    connect(mPlayer, &Bot::scoreUpdated, this, &GameAlgorithm::onPlayerScoreUpdated);

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

void GameAlgorithm::onKeyPressed(Keys key) { mKeyEvents.enqueue(key); }

void GameAlgorithm::onPlayerScoreUpdated() {
    if (mPlayer->currentScore() != currentLevel()->steps) return;

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

void GameAlgorithm::onTick() {
    if (!mKeyEvents.isEmpty())
        processKeyPress(mKeyEvents.dequeue());
}

void GameAlgorithm::processKeyPress(Keys key) {
    if (mHasWon) return;

    unsigned newRow = mPlayer->currentRow,
        newColumn = mPlayer->currentColumn,
        rows = mBoard->rows(),
        columns = mBoard->columns();
    char object = 0;

    const auto isBlock = [&](){ return mBoard->objectAt(newRow, newColumn) == BLOC_OBJ; };
    const auto setObject = [&](){ object = mBoard->objectAt(newRow, newColumn); };

    const auto checkNHandleCoin = [&](){
        if (object >= COIN_MIN_OBJ and object <= COIN_MAX_OBJ)
            mPlayer->incrementCurrentScore(object - COIN_MIN_OBJ + 1);
    };

    switch (key) {
        case Keys::W:
            if ((newRow = mPlayer->currentRow - 1) >= rows) break;
            if (isBlock()) break;

            setObject();

            mBoard->move(mPlayer->currentRow, mPlayer->currentColumn, newRow, newColumn);
            mPlayer->currentRow = newRow;

            checkNHandleCoin();

            emit boardChanged();
            break;
        case Keys::A:
            if ((newColumn = mPlayer->currentColumn - 1) >= columns) break;
            if (isBlock()) break;

            setObject();

            mBoard->move(mPlayer->currentRow, mPlayer->currentColumn, newRow, newColumn);
            mPlayer->currentColumn = newColumn;

            checkNHandleCoin();

            emit boardChanged();
            break;
        case Keys::S:
            if ((newRow = mPlayer->currentRow + 1) >= rows) break;
            if (isBlock()) break;

            setObject();

            mBoard->move(mPlayer->currentRow, mPlayer->currentColumn, newRow, newColumn);
            mPlayer->currentRow = newRow;

            checkNHandleCoin();

            emit boardChanged();
            break;
        case Keys::D:
            if ((newColumn = mPlayer->currentColumn + 1) >= columns) break;
            if (isBlock()) break;

            setObject();

            mBoard->move(mPlayer->currentRow, mPlayer->currentColumn, newRow, newColumn);
            mPlayer->currentColumn = newColumn;

            checkNHandleCoin();

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
            columns
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
                and row != startPos.first and column != startPos.second)
                mCurrentFreeCoords.push_back({ row, column });
        }
}

void GameAlgorithm::spawnEnemies() {
    mCurrentFreeCoords.clear();
    generateCoordsForEnemies();
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)

    for (char chr = ENEMY_MIN_OBJ; chr <= ENEMY_MAX_OBJ; chr++) {
        const auto position = mCurrentFreeCoords[rand() / (RAND_MAX / (mCurrentFreeCoords.size() - 1))]; // NOLINT(cert-msc50-cpp)
        mEnemies.push_back(new Bot(this, position.first, position.second, chr));
        mBoard->setAt(chr, position.first, position.second);
    }
}
