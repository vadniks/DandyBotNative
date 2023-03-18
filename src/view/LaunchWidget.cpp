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

#include "LaunchWidget.hpp"
#include "../consts.hpp"

LaunchWidget::LaunchWidget(QWidget* parent) :
    QWidget(parent),
    layout(this),
    appName(this),
    startGame(this)
{
    appName.setText(APP_NAME);
    appName.setFont(QFont(appName.font().family(), 12));
    appName.setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

    startGame.setText(START_GAME);
    startGame.setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
    connect(&startGame, &QPushButton::clicked, this, &LaunchWidget::onStartClicked);

    layout.setAlignment(Qt::AlignCenter);
    layout.addStretch();
    layout.addWidget(&appName);
    layout.addWidget(&startGame);
    layout.addStretch();
}
