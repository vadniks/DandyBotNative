/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QVector>
#include "../logic/GameAlgorithm.hpp"

class InfoWidget : public QWidget {
    Q_OBJECT
public:
    explicit InfoWidget(QWidget* parent, const GameAlgorithm& algorithm);
public slots:
    void onPlayerScoreChanged();
    void onLevelChanged(unsigned id);
private:
    void updateContent();

    QVBoxLayout mLayout;
    const GameAlgorithm& mAlgorithm;
    QLabel mCurrentLevel;
    QLabel mPlayerLabel;
};
