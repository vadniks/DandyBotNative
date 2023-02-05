
#include "GameLevel.hpp"

GameLevel::GameLevel(QObject* parent, unsigned int mapId, Position&& playerStart, unsigned int scoreToProceed) :
    QObject(parent), mapId(mapId), playerStart(playerStart), scoreToProceed(scoreToProceed)
{

}
