/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

#include <cassert>
#include "InfoWidget.hpp"
#include "../consts.hpp"

InfoWidget::InfoWidget(QWidget* parent, const GameAlgorithm& algorithm)
    : QWidget(parent), mLayout(this), mAlgorithm(algorithm)
{
    mLayout.addWidget(&mCurrentLevel);
    mLayout.addWidget(&mPlayerLabel);
    onPlayerScoreChanged();
    onLevelChanged(0);
    onEnemiesSpawned();
}

InfoWidget::~InfoWidget() {
    for (QLabel* label : mEnemies)
        delete label;
}

void InfoWidget::onPlayerScoreChanged()
{ mPlayerLabel.setText(QString::asprintf("%s: %d", PLAYER_SCORE, mAlgorithm.player()->totalScore())); }

void InfoWidget::onLevelChanged(unsigned id)
{ mCurrentLevel.setText(QString::asprintf("%s: %d", CURRENT_LEVEL, id)); }

void InfoWidget::onEnemiesSpawned() {
    for (QLabel* label : mEnemies)
        delete label;
    mEnemies.clear();

    for (const Bot* enemy : mAlgorithm.enemies()) {
        auto label = new QLabel(makeEnemyText(enemy->objectId, 0));
        mEnemies[enemy->objectId] = label;
        mLayout.addWidget(label);
    }
}

void InfoWidget::onEnemyScoreChanged(char objectId, unsigned score) {
    auto label = mEnemies.value(objectId, nullptr);
    assert(label != nullptr);
    label->setText(makeEnemyText(objectId, score));
}

QString InfoWidget::makeEnemyText(char objectId, unsigned score)
{ return QString::asprintf("%s %c's %s: %u", ENEMY, objectId, SCORE, score); }
