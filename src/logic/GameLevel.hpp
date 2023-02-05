
#pragma once

#include <QObject>
#include <tuple>

using Position = std::pair<unsigned, unsigned>;

class GameLevel : public QObject {
public:
    explicit GameLevel(QObject* parent, unsigned mapId, Position&& playerStart, unsigned scoreToProceed);

    const unsigned mapId;
    const Position playerStart;
    const unsigned scoreToProceed;
};
