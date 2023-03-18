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

#include "MainWidget.hpp"

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent), mLayout(this), mBoardWidget(this), mInfoWidget(nullptr, mBoardWidget.algorithm())
{
    mLayout.addWidget(&mBoardWidget, 0, Qt::AlignLeft);
    mLayout.addWidget(&mInfoWidget, 0, Qt::AlignRight | Qt::AlignTop);
    mLayout.setContentsMargins(0, 0, 0, 0);

    connect(&mBoardWidget, &BoardWidget::sizeChanged, this, &MainWidget::onBoardSizeChanged);
    connect(mBoardWidget.algorithm().player(), &Bot::scoreUpdated, &mInfoWidget, &InfoWidget::onPlayerScoreChanged);
    connect(&mBoardWidget.algorithm(), &GameAlgorithm::levelChanged, &mInfoWidget, &InfoWidget::onLevelChanged);
    connect(&mBoardWidget.algorithm(), &GameAlgorithm::enemyScoreChanged, &mInfoWidget, &InfoWidget::onEnemyScoreChanged);
    connect(&mBoardWidget.algorithm(), &GameAlgorithm::enemiesSpawned, &mInfoWidget, &InfoWidget::onEnemiesSpawned);
}

void MainWidget::onBoardSizeChanged(unsigned int, unsigned int) {
    const auto size = sizeHint();
    emit sizeChanged(size.width(), size.height());
}
