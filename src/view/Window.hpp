
#pragma once

#include <QMainWindow>

class Window final : public QMainWindow {
    Q_OBJECT
public:
    Window();
    ~Window() override;
private:
    QWidget* currentWidget;

    void onGameLaunched();
};
