
#pragma once

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "../util.hpp"

class LaunchWidget : public QWidget {
    Q_OBJECT
public:
    explicit LaunchWidget(QWidget* parent, Function onStartClicked, void* callbackParameter);
    ~LaunchWidget() override = default;
private:
    QVBoxLayout layout;
    QLabel appName;
    QPushButton startGame;
    Function onStartClickedCallback;
    void* callbackParameter;
private slots:
    void onStartClicked();
};
