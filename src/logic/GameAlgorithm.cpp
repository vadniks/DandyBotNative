
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QIcon>
#include "GameAlgorithm.hpp"
#include "../Exception.hpp"
#include "../consts.hpp"

GameAlgorithm::GameAlgorithm(QObject* parent) : QObject(parent), mBoard(nullptr), mPlayer(nullptr) {
    mObjectDescriptions[EMPTY_OBJ] = QIcon(EMPTY_ICON);
    mObjectDescriptions[BLOC_OBJ] = QIcon(BLOC_ICON);
    for (char i = COIN_MIN_OBJ; i <= COIN_MAX_OBJ; i++)
        mObjectDescriptions[i] = QIcon(COIN_ICON);
    for (char i = ENEMY_MIN_OBJ; i <= ENEMY_MAX_OBJ; i++)
        mObjectDescriptions[i] = QIcon(ENEMY_ICON);
    mObjectDescriptions[PLAYER_OBJ] = QIcon(PLAYER_ICON);

    loadGameData();
    const auto level = mLevels[0];
    setBoard(new GameBoard(this, level->rows, level->columns, QVector<char>(level->map)));

    unsigned row = level->start.second, column = level->start.first;
    mPlayer = new Player(this, row, column);
    mBoard->setAt(PLAYER_OBJ, row, column);
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

void GameAlgorithm::onKeyPressed(Keys key) {
    unsigned newRow = mPlayer->row, newColumn = mPlayer->column, rows = mBoard->rows(), columns = mBoard->columns();
    switch (key) {
        case Keys::W:
            if ((newRow = mPlayer->row - 1) >= rows) break;
            if (mBoard->objectAt(newRow, newColumn) == BLOC_OBJ) break;

            mBoard->move(mPlayer->row, mPlayer->column, newRow, newColumn);
            mPlayer->row = newRow;
            emit boardChanged();
            break;
        case Keys::A:
            if ((newColumn = mPlayer->column - 1) >= columns) break;
            if (mBoard->objectAt(newRow, newColumn) == BLOC_OBJ) break;

            mBoard->move(mPlayer->row, mPlayer->column, newRow, newColumn);
            mPlayer->column = newColumn;
            emit boardChanged();
            break;
        case Keys::S:
            if ((newRow = mPlayer->row + 1) >= rows) break;
            if (mBoard->objectAt(newRow, newColumn) == BLOC_OBJ) break;

            mBoard->move(mPlayer->row, mPlayer->column, newRow, newColumn);
            mPlayer->row = newRow;
            emit boardChanged();
            break;
        case Keys::D:
            if ((newColumn = mPlayer->column + 1) >= columns) break;
            if (mBoard->objectAt(newRow, newColumn) == BLOC_OBJ) break;

            mBoard->move(mPlayer->row, mPlayer->column, newRow, newColumn);
            mPlayer->column = newColumn;
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
        unsigned rows = 0, columns = 0;

        for (const QJsonValueRef& item : mapsArray[i].toArray()) {
            const auto string = item.toString();
            unsigned stringSize = 0;

            for (const QChar& qChar : string) {
                const char chr = qChar.toLatin1();
                if (!mObjectDescriptions.contains(chr))
                    throw Exception("map contains unknown character");

                map.push_back(chr);
                stringSize++;
            }
            rows++;

            if (columns != 0 and columns != stringSize) throw Exception("row sizes must be same");
            columns = stringSize;
        }

        mLevels.push_back(new GameLevel(
            this,
            static_cast<unsigned>(level[MAP].toInt()),
            GameLevel::Position(
                static_cast<unsigned>(position[0].toInt()),
                static_cast<unsigned>(position[1].toInt())
            ),
            static_cast<unsigned>(level[STEPS].toInt()),
            static_cast<QVector<char>&&>(map),
            rows,
            columns
        ));
    }

    file.close();
}
