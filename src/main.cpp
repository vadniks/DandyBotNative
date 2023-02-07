/*
 * Inspired by the work of Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

#include <QApplication>
#include "view/Window.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Window window;
    window.show();
    return QApplication::exec();
}
