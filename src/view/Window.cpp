
#include "Window.hpp"
#include "LaunchWidget.hpp"
#include "BoardWidget.hpp"
#include "../consts.hpp"

Window::Window() {
    setCentralWidget(currentWidget = new LaunchWidget(this, [this](){ onGameLaunched(); }));
    setMinimumSize(1280, 720);
    setWindowTitle(APP_NAME);
//    setWindowIcon();
    show();
}

Window::~Window() { delete currentWidget; }

void Window::onGameLaunched() {
    delete currentWidget;
    setCentralWidget(currentWidget = new BoardWidget(this));
}
