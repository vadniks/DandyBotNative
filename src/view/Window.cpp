
#include "Window.hpp"
#include "LaunchWidget.hpp"
#include "BoardWidget.hpp"
#include "../consts.hpp"

Window::Window() {
    currentWidget = new LaunchWidget(this);
    connect(((LaunchWidget*) currentWidget), &LaunchWidget::onStartClicked, this, &Window::onGameLaunched);
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
    connect(((BoardWidget*) currentWidget), &BoardWidget::sizeChanged, this, &Window::onSizeChanged);
    setCentralWidget(currentWidget);
}

void Window::onSizeChanged(unsigned int width, unsigned int height)
{ setFixedSize(static_cast<signed>(width), static_cast<signed>(height)); }
