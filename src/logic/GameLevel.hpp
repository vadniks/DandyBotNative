
#pragma once

#include <QObject>
#include <QPair>

class GameLevel : public QObject {
    Q_OBJECT
public:
    using Position = QPair<unsigned, unsigned>;
    GameLevel(QObject* parent, unsigned id, Position&& start, unsigned steps, QString&& map)
        : QObject(parent), mId(id), mStart(static_cast<Position&&>(start)), mSteps(steps), mMap(static_cast<QString&&>(map)) {};

    const unsigned mId;
    const Position mStart;
    const unsigned mSteps;
    const QString mMap;
};
