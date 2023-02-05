
#pragma once

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <functional>
#include "../util.hpp"

class LaunchWidget : public QWidget {
    Q_OBJECT
public:
    using Callback = std::function<void ()>;
    explicit LaunchWidget(QWidget* parent, Callback&& onStartClicked);
    ~LaunchWidget() override = default;
private:
    QVBoxLayout layout;
    QLabel appName;
    QPushButton startGame;
    Callback onStartClickedCallback;
private slots:
    void onStartClicked();
};
