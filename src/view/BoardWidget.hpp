
#pragma once

#include <QWidget>
#include "../logic/GameBoard.hpp"

class BoardWidget final : public QWidget {
    Q_OBJECT
public:
    explicit BoardWidget(QWidget* parent);
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    GameBoard* board;
};
