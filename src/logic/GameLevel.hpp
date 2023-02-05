
#pragma once

#include <QObject>
#include <tuple>

using Position = std::pair<unsigned, unsigned>;

class GameLevel final : public QObject {
    Q_OBJECT
public:
    GameLevel(
        QObject* parent,
        unsigned id,
        Position&& playerStart,
        unsigned scoreToProceed,
        QString&& map
    );

    const unsigned id;
    const Position playerStart;
    const unsigned scoreToProceed;
    const QString map;
};
