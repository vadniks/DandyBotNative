
#include "LaunchWidget.hpp"
#include "../consts.hpp"

LaunchWidget::LaunchWidget(QWidget* parent, Callback&& onStartClickedCallback) :
    layout(this),
    appName(this),
    startGame(this),
    onStartClickedCallback(onStartClickedCallback)
{
    appName.setText(APP_NAME);
    appName.setFont(QFont(appName.font().family(), 12));
    appName.setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

    startGame.setText("Start");
    startGame.setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
    connect(&startGame, &QPushButton::clicked, this, &LaunchWidget::onStartClicked);

    setParent(parent);
    layout.setAlignment(Qt::AlignCenter);
    layout.addStretch();
    layout.addWidget(&appName);
    layout.addWidget(&startGame);
    layout.addStretch();
}

void LaunchWidget::onStartClicked() { onStartClickedCallback(); }
