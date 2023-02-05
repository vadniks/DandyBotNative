
#pragma once

#include <QObject>

class Coin : public QObject {
    Q_OBJECT
public:
    explicit Coin(QObject* parent, unsigned amount);
    const unsigned amount;
};
