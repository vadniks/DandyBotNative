
#include <QPainter>
#include "BoardWidget.hpp"
#include "../consts.hpp"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent), mBoard(nullptr) {

}

void BoardWidget::setBoard(GameBoard* board) {
    if (mBoard != nullptr) delete mBoard;
    mBoard = board;
    updateGeometry();
}

QSize BoardWidget::sizeHint() const {
    return mBoard != nullptr ? QSize(
        static_cast<signed>(mBoard->mRows * GAME_OBJECT_SIZE),
        static_cast<signed>(mBoard->mColumns * GAME_OBJECT_SIZE)
    ) : QSize(0, 0);
}

QRect BoardWidget::objectRect(unsigned row, unsigned column) { return {
    static_cast<signed>(row),
    static_cast<signed>(column),
    static_cast<signed>(row + GAME_OBJECT_SIZE),
    static_cast<signed>(column + GAME_OBJECT_SIZE)
}; }

void BoardWidget::paintEvent(QPaintEvent*) {
    if (mBoard == nullptr) return;
    QPainter painter(this);

    painter.save();
    painter.setPen(QPen(QColor(255, 255, 255)));
    painter.setBrush(QBrush(QColor(100, 100, 100)));
    for (unsigned row = 0; row < mBoard->mRows; row++)
        for (unsigned column = 0; column < mBoard->mColumns; column++)
            painter.drawRect(objectRect(row, column).adjusted(5, 5, 5, 5));
    painter.restore();
}
