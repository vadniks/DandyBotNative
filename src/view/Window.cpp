
#include "Window.hpp"
#include "LaunchWidget.hpp"
#include "BoardWidget.hpp"
#include "../consts.hpp"

Window::Window() {
    setCentralWidget(currentWidget = new LaunchWidget(this, [this](){ onGameLaunched(); }));
    setFixedSize(static_cast<signed>(APP_WIDTH), static_cast<signed>(APP_HEIGHT));
    setWindowTitle(APP_NAME);
    setWindowIcon(QIcon(APP_ICON));
    show();
}

Window::~Window() { delete currentWidget; }

void Window::onGameLaunched() {
    delete currentWidget;
    setCentralWidget(currentWidget = new BoardWidget(this));
}
