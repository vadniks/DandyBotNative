/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 */

/*
 * GNU GPL v2
 *
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

#include "util.hpp"

extern unsigned APP_WIDTH;
extern unsigned APP_HEIGHT;
extern c_str APP_ICON;
extern c_str APP_NAME;
extern c_str START_GAME;
extern c_str GAME_DATA;
extern c_str LEVELS;
extern c_str MAP;
extern c_str START;
extern c_str STEPS;
extern c_str BOTS;
extern c_str MAPS;
extern const char EMPTY_OBJ;
extern const char BLOC_OBJ;
extern const char COIN_MIN_OBJ;
extern const char COIN_MAX_OBJ;
extern const char ENEMY_MIN_OBJ;
extern const char ENEMY_MAX_OBJ;
extern const char PLAYER_OBJ;
extern unsigned GAME_OBJECT_SIZE;
extern c_str EMPTY_ICON;
extern c_str BLOC_ICON;
extern c_str COIN_ICON;
extern c_str ENEMY_ICON_PREFIX;
extern c_str ICON_SUFFIX;
extern c_str PLAYER_ICON;
extern c_str YOU_WON;
extern c_str PLAYER_SCORE;
extern c_str CURRENT_LEVEL;
extern unsigned TICK_INTERVAL;
extern float BOT_MOVE_CHANCE;
extern float BOT_COIN_TAKE_CHANCE;
extern float PLAYER_SCORE_TO_WIN_MULTIPLIER;
extern c_str ENEMY;
extern c_str SCORE;
extern c_str SCRIPT_LIB_NAME;
extern c_str SCRIPT_FUN_NAME;
extern int NUM_UNDEF;
