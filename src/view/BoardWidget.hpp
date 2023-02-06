
#pragma once

#include <QWidget>
#include <QPointer>
#include "../logic/GameBoard.hpp"

class BoardWidget final : public QWidget {
    Q_OBJECT
public:
    explicit BoardWidget(QWidget* parent);
    void setBoard(GameBoard* board);
    [[nodiscard]] QSize sizeHint() const override;
    [[nodiscard]] static QRect objectRect(unsigned row, unsigned column);
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    GameBoard* mBoard;
};
