/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

#pragma once

#include <QMainWindow>

class Window final : public QMainWindow {
    Q_OBJECT
public:
    Window();
    ~Window() override;
private:
    QWidget* currentWidget;
private slots:
    void onGameLaunched();
    void onSizeChanged(unsigned width, unsigned height);
};
