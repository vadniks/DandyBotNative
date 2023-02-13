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

#include "Window.hpp"
#include "LaunchWidget.hpp"
#include "MainWidget.hpp"
#include "../consts.hpp"

Window::Window() {
    currentWidget = new LaunchWidget(this);
    connect(dynamic_cast<LaunchWidget*>(currentWidget), &LaunchWidget::onStartClicked, this, &Window::onGameLaunched);
    setCentralWidget(currentWidget);

    setFixedSize(static_cast<signed>(APP_WIDTH / 3), static_cast<signed>(APP_HEIGHT / 3));
    setWindowTitle(APP_NAME);
    setWindowIcon(QIcon(APP_ICON));
    show();
}

Window::~Window() { delete currentWidget; }

void Window::onGameLaunched() {
    delete currentWidget;
    currentWidget = new MainWidget(this);
    connect(dynamic_cast<MainWidget*>(currentWidget), &MainWidget::sizeChanged, this, &Window::onSizeChanged);
    setCentralWidget(currentWidget);
    setFixedSize(currentWidget->sizeHint());
}

void Window::onSizeChanged(unsigned int width, unsigned int height)
{ setFixedSize(static_cast<signed>(width), static_cast<signed>(height)); }
