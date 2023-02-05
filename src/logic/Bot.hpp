
#pragma once

#include <QObject>

class Bot : public QObject {
    Q_OBJECT
public:
    explicit Bot(QObject* parent, bool enemy);
    const bool enemy;
};
