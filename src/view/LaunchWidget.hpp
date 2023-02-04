
#pragma once

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <functional>
#include "../util.hpp"

using Callback = std::function<void ()>;

class LaunchWidget : public QWidget {
    Q_OBJECT
public:
    explicit LaunchWidget(QWidget* parent, Callback onStartClicked);
    ~LaunchWidget() override = default;
private:
    QVBoxLayout layout;
    QLabel appName;
    QPushButton startGame;
    Callback onStartClickedCallback;
private slots:
    void onStartClicked();
};
