
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "GameData.hpp"
#include <QException>
#include "../consts.hpp"

GameData::GameData(QObject* parent) : QObject(parent) {
    auto file = QFile(GAME_DATA);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    auto document = QJsonDocument::fromJson(file.readAll());
    auto json = document.object();
    auto levelsArray = json[LEVELS].toArray();
    auto mapsArray = json[MAPS].toArray();

    const unsigned size = levelsArray.size();
    if (size != mapsArray.size()) throw QException();

    for (unsigned i = 0; i <= size; i++) {
        auto level = levelsArray[i].toObject();
        auto position = level[START].toArray();

        levels.push_back(new GameLevel(
            this,
            static_cast<unsigned>(level[MAP].toInt()),
            Position(
                static_cast<unsigned>(position[0].toInt()),
                static_cast<unsigned>(position[1].toInt())
            ),
            static_cast<unsigned>(level[STEPS].toInt()),
            mapsArray[i].toString()
        ));

    }

    file.close();
}

GameData::~GameData() {
    for (const GameLevel*& item : levels)
        delete item;
}
