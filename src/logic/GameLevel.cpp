
#include "GameLevel.hpp"

GameLevel::GameLevel(
    QObject* parent,
    unsigned id,
    Position&& playerStart,
    unsigned scoreToProceed,
    QString&& map
) :
    QObject(parent),
    id(id),
    playerStart(playerStart),
    scoreToProceed(scoreToProceed),
    map(map)
{}
