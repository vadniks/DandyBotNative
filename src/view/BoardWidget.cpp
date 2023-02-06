
#include <QPainter>
#include "BoardWidget.hpp"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent) {

}

void BoardWidget::setBoard(GameBoard* board) {
    if (board == mBoard) return;
    if (!mBoard.isNull())
        mBoard->disconnect(this);
    mBoard = board;
    updateGeometry();
}

void BoardWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
}
