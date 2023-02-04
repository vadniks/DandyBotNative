
#include "Window.hpp"
#include "LaunchWidget.hpp"
#include "consts.hpp"

Window::Window() {
    currentWidget = new LaunchWidget(this);
    setCentralWidget(currentWidget);
    setMinimumSize(1280, 720);
    setWindowTitle(APP_NAME);
//    setWindowIcon();
    show();
}

Window::~Window() {
    delete currentWidget;
}
