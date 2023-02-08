/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

#include "InfoWidget.hpp"
#include "../consts.hpp"

InfoWidget::InfoWidget(QWidget* parent, const GameAlgorithm& algorithm)
    : QWidget(parent), mLayout(this), mAlgorithm(algorithm)
{
    mLayout.addWidget(&mPlayerLabel);
    updateContent();
}

InfoWidget::~InfoWidget() {
    for (const QLabel* label : mEnemyLabels)
        delete label;
}

void InfoWidget::onPlayerScoreChanged() { updateContent(); }

void InfoWidget::updateContent() {
    mPlayerLabel.setText(QString::asprintf("%s %d", PLAYER_SCORE, mAlgorithm.player()->totalScore()));
}
