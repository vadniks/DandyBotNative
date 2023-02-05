
#pragma once

#include <QObject>
#include <tuple>
#include <vector>

using Position = std::pair<unsigned, unsigned>;
using std::vector;

class GameLevel final : public QObject {
    Q_OBJECT
public:
    GameLevel(
        QObject* parent,
        unsigned id,
        Position&& playerStart,
        unsigned scoreToProceed,
        const QString& map
    );
    ~GameLevel() override;

    const unsigned id;
    const Position playerStart;
    const unsigned scoreToProceed;
    vector<vector<const QObject*>*> matrix;
};
