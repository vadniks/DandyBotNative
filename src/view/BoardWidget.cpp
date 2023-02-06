
#include <QPainter>
#include "BoardWidget.hpp"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent), mBoard(nullptr) {

}

void BoardWidget::setBoard(GameBoard* board) {
    if (mBoard != nullptr) delete mBoard;
    mBoard = board;
    updateGeometry();
}

void BoardWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
}
