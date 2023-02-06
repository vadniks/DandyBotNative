
#include <QPainter>
#include "BoardWidget.hpp"
#include "../consts.hpp"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent), mAlgorithm(this), mBoard(nullptr) {
    connect(&mAlgorithm, &GameAlgorithm::boardChanged, this, &BoardWidget::onBoardChanged);
    setBoard(mAlgorithm.board());
}

void BoardWidget::setBoard(GameBoard* board) {
    if (mBoard != nullptr) delete mBoard;
    mBoard = board;
    connect(mBoard, &GameBoard::boardUpdated, this, &BoardWidget::onBoardChanged);
    updateGeometry();
}

QSize BoardWidget::sizeHint() const {
    return mBoard != nullptr ? QSize(
        static_cast<signed>(mBoard->columns() * GAME_OBJECT_SIZE),
        static_cast<signed>(mBoard->rows() * GAME_OBJECT_SIZE)
    ) : QSize(0, 0);
}

QRect BoardWidget::objectRect(unsigned row, unsigned column) { return {
    static_cast<signed>(column * GAME_OBJECT_SIZE),
    static_cast<signed>(row * GAME_OBJECT_SIZE),
    static_cast<signed>(GAME_OBJECT_SIZE),
    static_cast<signed>(GAME_OBJECT_SIZE)
}; }

void BoardWidget::onBoardChanged() { setBoard(mAlgorithm.board()); }

void BoardWidget::paintEvent(QPaintEvent*) {
    if (mBoard == nullptr) return;
    QPainter painter(this);

    painter.save();
    painter.setPen(QPen(QColor(0, 0, 0)));
    painter.setBrush(QBrush(QColor(100, 100, 100)));
    for (unsigned row = 0; row < mBoard->rows(); row++)
        for (unsigned column = 0; column < mBoard->columns(); column++)
            painter.drawRect(objectRect(row, column));
    painter.restore();
}
