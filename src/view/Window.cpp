/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

#include "Window.hpp"
#include "LaunchWidget.hpp"
#include "BoardWidget.hpp"
#include "../consts.hpp"

Window::Window() {
    currentWidget = new LaunchWidget(this);
    connect(dynamic_cast<LaunchWidget*>(currentWidget), &LaunchWidget::onStartClicked, this, &Window::onGameLaunched);
    setCentralWidget(currentWidget);

    setFixedSize(static_cast<signed>(APP_WIDTH), static_cast<signed>(APP_HEIGHT));
    setWindowTitle(APP_NAME);
    setWindowIcon(QIcon(APP_ICON));
    show();
}

Window::~Window() { delete currentWidget; }

void Window::onGameLaunched() {
    delete currentWidget;
    currentWidget = new BoardWidget(this);
    connect(dynamic_cast<BoardWidget*>(currentWidget), &BoardWidget::sizeChanged, this, &Window::onSizeChanged);
    setCentralWidget(currentWidget);
    setFixedSize(currentWidget->sizeHint());
}

void Window::onSizeChanged(unsigned int width, unsigned int height)
{ setFixedSize(static_cast<signed>(width), static_cast<signed>(height)); }
