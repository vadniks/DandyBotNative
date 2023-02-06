
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QException>
#include "GameAlgorithm.hpp"
#include "../consts.hpp"

GameAlgorithm::GameAlgorithm(QObject* parent) : QObject(parent), mBoard(nullptr) {
    QVector<char> objects;
    objects.fill('#', 24 * 42);
    setBoard(new GameBoard(this, 24, 42, static_cast<decltype(objects)&&>(objects)));
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
        auto map = mapsArray[i].toArray();

        mLevels.push_back(new GameLevel(
            this,
            static_cast<unsigned>(level[MAP].toInt()),
            GameLevel::Position(
                static_cast<unsigned>(position[0].toInt()),
                static_cast<unsigned>(position[1].toInt())
            ),
            static_cast<unsigned>(level[STEPS].toInt()),
            ""
        ));
    }

    file.close();
}
