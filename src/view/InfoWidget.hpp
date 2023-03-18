/*
 * Copyright (c) 2021 Peter Sovietov (https://github.com/true-grue)
 *
 * Copyright (C) 2023 Vad Nik (https://github.com/vadniks)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "../logic/GameAlgorithm.hpp"

class InfoWidget : public QWidget {
    Q_OBJECT
public:
    explicit InfoWidget(QWidget* parent, const GameAlgorithm& algorithm);
    ~InfoWidget() override;
public slots:
    void onPlayerScoreChanged();
    void onLevelChanged(unsigned id);
    void onEnemiesSpawned();
    void onEnemyScoreChanged(char objectId, unsigned score);
private:
    static QString makeEnemyText(char objectId, unsigned score);

    QVBoxLayout mLayout;
    const GameAlgorithm& mAlgorithm;
    QLabel mCurrentLevel;
    QLabel mPlayerLabel;
    QMap<char, QLabel*> mEnemies;
};
