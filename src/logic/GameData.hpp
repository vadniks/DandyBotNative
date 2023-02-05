
#pragma once

#include <QObject>
#include <vector>
#include "GameLevel.hpp"

class GameData final : public QObject {
    Q_OBJECT
public:
    explicit GameData(QObject* parent);
    ~GameData() override;

    std::vector<const GameLevel*> levels;
};
