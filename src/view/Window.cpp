
#include "Window.hpp"
#include "LaunchWidget.hpp"
#include "../consts.hpp"
#include <QDebug>

Window::Window() {
    currentWidget = new LaunchWidget(this, [](void* _this){ ((Window*) _this)->onGameLaunched(); }, this);
    setCentralWidget(currentWidget);
    setMinimumSize(1280, 720);
    setWindowTitle(APP_NAME);
//    setWindowIcon();
    show();
}

Window::~Window() { delete currentWidget; }

void Window::onGameLaunched() {
    qDebug() << "rrdfgvrdf\n";
}
