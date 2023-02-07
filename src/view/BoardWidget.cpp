
#include <QPainter>
#include "BoardWidget.hpp"
#include "../consts.hpp"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent), mAlgorithm(this), mBoard(nullptr) {
    connect(&mAlgorithm, &GameAlgorithm::boardChanged, this, &BoardWidget::onBoardChanged);
    setBoard(mAlgorithm.board());
}

void BoardWidget::setBoard(GameBoard* board) {
    if (board == mBoard) {
        update();
        return;
    }

    delete mBoard;
    mBoard = board;
    connect(mBoard, &GameBoard::boardUpdated, this, &BoardWidget::onBoardChanged);
    setFixedSize(sizeHint());
    updateGeometry();

    auto size = sizeHint();
    emit sizeChanged(size.width(), size.height());
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
    auto size = sizeHint();
    painter.fillRect(QRect(0, 0, size.width(), size.height()), QColor::fromRgb(0, 0, 0));
    painter.restore();

    painter.save();
    for (unsigned row = 0; row < mBoard->rows(); row++)
        for (unsigned column = 0; column < mBoard->columns(); column++)
            iconOf(mBoard->objectAt(row, column)).paint(&painter, objectRect(row, column), Qt::AlignCenter);
    painter.restore();
}

QIcon BoardWidget::iconOf(char object) { return mAlgorithm.objectDescriptions().value(object); }
