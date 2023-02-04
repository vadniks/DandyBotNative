
#pragma once

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class LaunchWidget : public QWidget {
    Q_OBJECT
public:
    explicit LaunchWidget(QWidget* parent);
    ~LaunchWidget() override = default;
private:
    QVBoxLayout layout;
    QLabel appName;
    QPushButton startGame;
};
