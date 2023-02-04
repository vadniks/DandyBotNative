
#include "Window.hpp"
#include "launchWidget.hpp"

Window::Window() {
    currentWidget = new LaunchWidget(this);
    setCentralWidget(currentWidget);
//    setWindowState(Qt::WindowState::WindowFullScreen);
    setMinimumSize(1024, 576);
    show();
}

Window::~Window() {
    delete currentWidget;
}
