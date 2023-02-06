
#pragma once

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "../util.hpp"

class LaunchWidget final : public QWidget {
    Q_OBJECT
public:
    explicit LaunchWidget(QWidget* parent);
private:
    QVBoxLayout layout;
    QLabel appName;
    QPushButton startGame;
signals:
    void onStartClicked();
};
