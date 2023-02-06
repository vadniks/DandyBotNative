
#include <QPainter>
#include "BoardWidget.hpp"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent), mBoard(nullptr) {

}

void BoardWidget::setBoard(GameBoard* board) {
    if (board == mBoard) return;
    if (mBoard != nullptr) delete mBoard;
    mBoard = board;
    updateGeometry();
}

void BoardWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
}
