/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 */

/*
 * GNU GPL v2
 *
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
        static_cast<signed>(mBoard->rows() * GAME_OBJECT_SIZE)
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
    for (unsigned row = 0; row < mBoard->rows(); row++)
        for (unsigned column = 0; column < mBoard->columns(); column++)
            iconOf(mBoard->objectAt(row, column)).paint(&painter, objectRect(row, column), Qt::AlignCenter);
    painter.restore();
}

void BoardWidget::keyPressEvent(QKeyEvent* event) { switch (event->key()) {
    case KeyEvent::W: emit keyPressed(KeyEvent::W); break;
    case KeyEvent::A: emit keyPressed(KeyEvent::A); break;
    case KeyEvent::S: emit keyPressed(KeyEvent::S); break;
    case KeyEvent::D: emit keyPressed(KeyEvent::D); break;
} }

QIcon BoardWidget::iconOf(char object) { return mAlgorithm.objectDescriptions().value(object); }
