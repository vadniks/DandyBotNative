
#pragma once

#include <QObject>

class Bot : public QObject {
public:
    explicit Bot(QObject* parent, bool enemy);
    const bool enemy;
};
