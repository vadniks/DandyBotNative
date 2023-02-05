
#pragma once

#include <QObject>
#include <QVector>
#include "GameLevel.hpp"

class GameData final : public QObject {
    Q_OBJECT
public:
    explicit GameData(QObject* parent);
    ~GameData() override;

    QVector<const GameLevel*> levels;
};
