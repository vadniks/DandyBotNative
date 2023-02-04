
#include "LaunchWidget.hpp"
#include "consts.hpp"

LaunchWidget::LaunchWidget(QWidget* parent) :
    layout(this), appName(this), startGame(this)
{
    setParent(parent);
    layout.setAlignment(Qt::AlignCenter);

    layout.addStretch();

    appName.setText(APP_NAME);
    appName.setFont(QFont(appName.font().family(), 12));
    appName.setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
    layout.addWidget(&appName);

    startGame.setText("Start");
    startGame.setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
    layout.addWidget(&startGame);

    layout.addStretch();
}
