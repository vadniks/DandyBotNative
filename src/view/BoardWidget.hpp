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

#pragma once

#include <QWidget>
#include <QPointer>
#include <QKeyEvent>
#include "../logic/GameBoard.hpp"
#include "../logic/GameAlgorithm.hpp"
#include "../KeyEvent.hpp"

class BoardWidget final : public QWidget {
    Q_OBJECT
public:
    explicit BoardWidget(QWidget* parent);
    void setBoard(GameBoard* board);
    [[nodiscard]] QSize sizeHint() const override;
    [[nodiscard]] static QRect objectRect(unsigned row, unsigned column);
    [[nodiscard]] const GameAlgorithm& algorithm() const;
public slots:
    void onBoardChanged();
signals:
    void sizeChanged(unsigned width, unsigned height);
    void keyPressed(KeyEvent key);
protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
private:
    QIcon iconOf(char object);

    GameAlgorithm mAlgorithm;
    GameBoard* mBoard;
};
