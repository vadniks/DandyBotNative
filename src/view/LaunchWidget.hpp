/*
 * Inspired by the work of Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

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
