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

#define EMPTY ' '
#define BLOCK '#'
#define COIN_MIN '1'
#define COIN_MAX '9'
#define ENEMY_MIN 'a'
#define ENEMY_MAX 'f'
#define PLAYER '!'

#define UP 87
#define LEFT 65
#define DOWN 83
#define RIGHT 68
#define PASS -1

/**
 * Returns an action to be performed by the player bot at the current bot tick.
 * This function is called on every bot tick event.
 *
 * Coin objects are taken automatically when bot enters theirs coordinates.
 *
 * @param row - the y coordinate starting from left top
 * @param column - the x coordinate starting from left top
 * @param level - current level id starting from 0
 * @param objectIds - an array containing 4 object ids for all directions at the current tick,
 *        contains: {up, left, down, right}, array is deallocated automatically
 *
 * @return one of UP, LEFT, DOWN, RIGHT, PASS
 */
char script(unsigned row, unsigned column, unsigned level, char* objectIds);
