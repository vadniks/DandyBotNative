/*
 * Inspired by the work of Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

#include "LaunchWidget.hpp"
#include "../consts.hpp"

LaunchWidget::LaunchWidget(QWidget* parent) :
    QWidget(parent),
    layout(this),
    appName(this),
    startGame(this)
{
    appName.setText(APP_NAME);
    appName.setFont(QFont(appName.font().family(), 12));
    appName.setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

    startGame.setText(START_GAME);
    startGame.setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
    connect(&startGame, &QPushButton::clicked, this, &LaunchWidget::onStartClicked);

    layout.setAlignment(Qt::AlignCenter);
    layout.addStretch();
    layout.addWidget(&appName);
    layout.addWidget(&startGame);
    layout.addStretch();
}
