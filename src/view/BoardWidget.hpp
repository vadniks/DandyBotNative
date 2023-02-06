
#pragma once

#include <QWidget>
#include <QPointer>
#include "../logic/GameBoard.hpp"

class BoardWidget final : public QWidget {
    Q_OBJECT
public:
    explicit BoardWidget(QWidget* parent);
    void setBoard(GameBoard* board);
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    QPointer<GameBoard> mBoard;
};
