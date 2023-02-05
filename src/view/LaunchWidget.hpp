
#pragma once

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <functional>
#include "../util.hpp"

class LaunchWidget final : public QWidget {
    Q_OBJECT
public:
    using Callback = std::function<void ()>;
    explicit LaunchWidget(QWidget* parent, Callback&& onStartClicked);
private:
    QVBoxLayout layout;
    QLabel appName;
    QPushButton startGame;
    Callback onStartClickedCallback;
private slots:
    void onStartClicked();
};
