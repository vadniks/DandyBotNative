
#pragma once

#include <QObject>

class Block : public QObject {
    Q_OBJECT
public:
    explicit Block(QObject* parent);
};
