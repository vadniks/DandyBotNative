
#include "MainWidget.hpp"

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent), mLayout(this), mBoardWidget(this), mInfoWidget(nullptr, mBoardWidget.algorithm())
{
    mLayout.addWidget(&mBoardWidget, 0, Qt::AlignLeft);
    mLayout.addWidget(&mInfoWidget, 0, Qt::AlignRight | Qt::AlignTop);
    mLayout.setContentsMargins(0, 0, 0, 0);

    connect(&mBoardWidget, &BoardWidget::sizeChanged, this, &MainWidget::onBoardSizeChanged);
    connect(mBoardWidget.algorithm().player(), &Bot::scoreUpdated, &mInfoWidget, &InfoWidget::onPlayerScoreChanged);
    connect(&mBoardWidget.algorithm(), &GameAlgorithm::levelChanged, &mInfoWidget, &InfoWidget::onLevelChanged);
    connect(&mBoardWidget.algorithm(), &GameAlgorithm::enemyScoreChanged, &mInfoWidget, &InfoWidget::onEnemyScoreChanged);
    connect(&mBoardWidget.algorithm(), &GameAlgorithm::enemiesSpawned, &mInfoWidget, &InfoWidget::onEnemiesSpawned);
}

void MainWidget::onBoardSizeChanged(unsigned int, unsigned int) {
    const auto size = sizeHint();
    emit sizeChanged(size.width(), size.height());
}
