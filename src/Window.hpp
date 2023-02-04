
#pragma once

#include <QMainWindow>

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window();
    ~Window() override;
private:
    QWidget* currentWidget;
};
