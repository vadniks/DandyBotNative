
#include <QApplication>
#include "view/Window.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Window window;
    window.show();
    return QApplication::exec();
}