/*
 * Copyright (c) 2021 Peter Sovietov (https://github.com/true-grue)
 *
 * Copyright (C) 2023 Vad Nik (https://github.com/vadniks)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#include <QPainter>
#include "BoardWidget.hpp"
#include "../consts.hpp"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent), mAlgorithm(this), mBoard(nullptr) {
    connect(&mAlgorithm, &GameAlgorithm::boardChanged, this, &BoardWidget::onBoardChanged);
    setBoard(mAlgorithm.board());
    setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    connect(this, &BoardWidget::keyPressed, &mAlgorithm, &GameAlgorithm::onKeyPressed);
}

void BoardWidget::setBoard(GameBoard* board) {
    if (board == mBoard) {
        update();
        return;
    }

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
        static_cast<signed>((mBoard->rows() + 2) * GAME_OBJECT_SIZE)
    ) : QSize(0, 0);
}

QRect BoardWidget::objectRect(unsigned row, unsigned column) { return {
    static_cast<signed>(column * GAME_OBJECT_SIZE),
    static_cast<signed>(row * GAME_OBJECT_SIZE),
    static_cast<signed>(GAME_OBJECT_SIZE),
    static_cast<signed>(GAME_OBJECT_SIZE)
}; }

const GameAlgorithm& BoardWidget::algorithm() const { return mAlgorithm; }

void BoardWidget::onBoardChanged() { setBoard(mAlgorithm.board()); }

void BoardWidget::paintEvent(QPaintEvent*) {
    if (mBoard == nullptr) return;
    QPainter painter(this);

    painter.save();
    auto size = sizeHint();
    painter.fillRect(QRect(0, 0, size.width(), size.height()), QColor::fromRgb(0, 0, 0));
    painter.restore();

    painter.save();
    const auto rows = mBoard->rows(), columns= mBoard->columns();
    for (unsigned row = 0; row < rows; row++)
        for (unsigned column = 0; column < columns; column++)
            iconOf(mBoard->objectAt(row, column)).paint(&painter, objectRect(row, column), Qt::AlignCenter);
    painter.restore();

    painter.save();
    painter.setPen(QColor::fromRgb(255, 255, 255));
    painter.setBrush(QColor::fromRgb(255, 255, 255));
    const auto icons = mAlgorithm.objectDescriptions();
    const auto offset = static_cast<signed>(GAME_OBJECT_SIZE);
    for (char chr = ENEMY_MIN_OBJ, i = 0; chr < ENEMY_MAX_OBJ; chr++, i++) {
        if (static_cast<unsigned>(i) >= columns) break;

        const auto rect = objectRect(rows, i).adjusted(0, 2, 0, 2);
        icons[chr].paint(&painter, rect);

        painter.drawText(rect.adjusted(offset / 2, offset, 0, offset), QString(chr));
    }
    painter.restore();

    painter.save();
    painter.setPen(QColor::fromRgb(255, 255, 255));
    painter.setBrush(QColor::fromRgb(255, 255, 255));
    const auto offset2 = static_cast<signed>(rows * offset - 1);
    painter.drawLine(0, offset2, static_cast<signed>(columns) * offset - 1, offset2);
    painter.restore();
}

void BoardWidget::keyPressEvent(QKeyEvent* event) { switch (event->key()) {
    case KeyEvent::W: emit keyPressed(KeyEvent::W); break;
    case KeyEvent::A: emit keyPressed(KeyEvent::A); break;
    case KeyEvent::S: emit keyPressed(KeyEvent::S); break;
    case KeyEvent::D: emit keyPressed(KeyEvent::D); break;
} }

QIcon BoardWidget::iconOf(char object) { return mAlgorithm.objectDescriptions().value(object); }
