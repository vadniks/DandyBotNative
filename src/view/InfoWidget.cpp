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

InfoWidget::InfoWidget(QWidget* parent, const GameAlgorithm& algorithm) : QWidget(parent), mLayout(this), mAlgorithm(algorithm) {
//    setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed));
//    mLayout.setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
    mLayout.addWidget(new QLabel("vgfrvgfrgv"));
    updateContent();
}

InfoWidget::~InfoWidget() {
    for (const QLabel* label : mEnemyLabels)
        delete label;
}

void InfoWidget::updateContent() {
    mPlayerLabel.setText(QString::asprintf("%d", mAlgorithm.player()->totalScore()));
}
