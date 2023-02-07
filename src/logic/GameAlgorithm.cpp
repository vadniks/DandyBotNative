
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QException>
#include <QIcon>
#include "GameAlgorithm.hpp"
#include "../consts.hpp"

GameAlgorithm::GameAlgorithm(QObject* parent) : QObject(parent), mBoard(nullptr) {
//    QVector<char> objects;
//    objects.fill('#', 24 * 42);
//    setBoard(new GameBoard(this, 24, 42, static_cast<decltype(objects)&&>(objects)));

    mObjectDescriptions[EMPTY_OBJ] = QIcon(EMPTY_ICON);
    mObjectDescriptions[BLOC_OBJ] = QIcon(BLOC_ICON);
    for (char i = COIN_MIN_OBJ; i <= COIN_MAX_OBJ; i++)
        mObjectDescriptions[i] = QIcon(COIN_ICON);
    for (char i = ENEMY_MIN_OBJ; i <= ENEMY_MAX_OBJ; i++)
        mObjectDescriptions[i] = QIcon(ENEMY_ICON);
    mObjectDescriptions[BOT_OBJ] = QIcon(BOT_ICON);

    loadGameData();
    const auto level = mLevels[0];
    setBoard(new GameBoard(this, level->rows, level->columns, QVector<char>(level->map)));
}

GameAlgorithm::~GameAlgorithm() {
    delete mBoard;
    for (const GameLevel* item : mLevels) delete item;
}

GameBoard* GameAlgorithm::board() const { return mBoard; }

void GameAlgorithm::setBoard(GameBoard* board) {
    delete mBoard;
    mBoard = board;
    emit boardChanged();
}

const QMap<char, QIcon>& GameAlgorithm::objectDescriptions() { return mObjectDescriptions; }

void GameAlgorithm::loadGameData() EXCEPT {
    auto file = QFile(GAME_DATA);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    auto document = QJsonDocument::fromJson(file.readAll());
    auto json = document.object();
    auto levelsArray = json[LEVELS].toArray();
    auto mapsArray = json[MAPS].toArray();

    const unsigned size = levelsArray.size();
    if (size != mapsArray.size()) throw QException();

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
                    throw QException();

                map.push_back(chr);
                stringSize++;
            }
            rows++;

            if (columns != 0 and columns != stringSize) throw QException();
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
