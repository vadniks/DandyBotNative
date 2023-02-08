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
#include "GameAlgorithm.hpp"
#include "../Exception.hpp"
#include "../consts.hpp"

GameAlgorithm::GameAlgorithm(QObject* parent)
    : QObject(parent), mBoard(nullptr), mPlayer(nullptr), mCurrentLevelId(0), mHasWon(false)
{
    mObjectDescriptions[EMPTY_OBJ] = QIcon(EMPTY_ICON);
    mObjectDescriptions[BLOC_OBJ] = QIcon(BLOC_ICON);
    for (char i = COIN_MIN_OBJ; i <= COIN_MAX_OBJ; i++)
        mObjectDescriptions[i] = QIcon(COIN_ICON);
    for (char i = ENEMY_MIN_OBJ; i <= ENEMY_MAX_OBJ; i++)
        mObjectDescriptions[i] = QIcon(ENEMY_ICON);
    mObjectDescriptions[PLAYER_OBJ] = QIcon(PLAYER_ICON);

    loadGameData();
    setBoard(makeBoard(currentLevel()));

    mPlayer = new Player(this, 0, 0);
    initializePlayer();

    connect(mPlayer, &Player::scoreUpdated, this, &GameAlgorithm::onPlayerScoreUpdated);
}

GameAlgorithm::~GameAlgorithm() {
    delete mBoard;
    for (const GameLevel* item : mLevels) delete item;
    delete mPlayer;
}

GameBoard* GameAlgorithm::board() const { return mBoard; }

void GameAlgorithm::setBoard(GameBoard* board) {
    delete mBoard;
    mBoard = board;
    emit boardChanged();
}

const QMap<char, QIcon>& GameAlgorithm::objectDescriptions() { return mObjectDescriptions; }

const Player* GameAlgorithm::player() const { return mPlayer; }

void GameAlgorithm::onKeyPressed(Keys key) {
    if (mHasWon) return;

    unsigned newRow = mPlayer->row,
        newColumn = mPlayer->column,
        rows = mBoard->rows(),
        columns = mBoard->columns();
    char object = 0;

    const auto isBlock = [&](){ return mBoard->objectAt(newRow, newColumn) == BLOC_OBJ; };
    const auto setObject = [&](){ object = mBoard->objectAt(newRow, newColumn); };

    const auto checkNHandleCoin = [&](){
        if (object >= COIN_MIN_OBJ and object <= COIN_MAX_OBJ)
            mPlayer->updateCurrentScore(object - COIN_MIN_OBJ + 1, true);
    };

    switch (key) {
        case Keys::W:
            if ((newRow = mPlayer->row - 1) >= rows) break;
            if (isBlock()) break;

            setObject();

            mBoard->move(mPlayer->row, mPlayer->column, newRow, newColumn);
            mPlayer->row = newRow;

            checkNHandleCoin();

            emit boardChanged();
            break;
        case Keys::A:
            if ((newColumn = mPlayer->column - 1) >= columns) break;
            if (isBlock()) break;

            setObject();

            mBoard->move(mPlayer->row, mPlayer->column, newRow, newColumn);
            mPlayer->column = newColumn;

            checkNHandleCoin();

            emit boardChanged();
            break;
        case Keys::S:
            if ((newRow = mPlayer->row + 1) >= rows) break;
            if (isBlock()) break;

            setObject();

            mBoard->move(mPlayer->row, mPlayer->column, newRow, newColumn);
            mPlayer->row = newRow;

            checkNHandleCoin();

            emit boardChanged();
            break;
        case Keys::D:
            if ((newColumn = mPlayer->column + 1) >= columns) break;
            if (isBlock()) break;

            setObject();

            mBoard->move(mPlayer->row, mPlayer->column, newRow, newColumn);
            mPlayer->column = newColumn;

            checkNHandleCoin();

            emit boardChanged();
            break;
    }
}

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

            if (columns != 0 and columns != stringSize) throw Exception("row sizes must be same");
            columns = stringSize;
        }

        const unsigned steps = level[STEPS].toInt();
        if (coins != steps) throw Exception("amount of steps must be equal to amount of coin objects on the map");

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

    mPlayer->row = row;
    mPlayer->column = column;
    mBoard->setAt(PLAYER_OBJ, row, column);
}
