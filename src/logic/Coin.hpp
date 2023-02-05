
#pragma once

#include <QObject>

class Coin : public QObject {
public:
    explicit Coin(QObject* parent, unsigned amount);
    const unsigned amount;
};
