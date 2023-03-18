/*
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

#include "defs.h"

/**
 * Returns an action to be performed by the player bot at the current bot tick.
 * This function is called on every bot tick event.
 *
 * Coin objects are taken automatically when bot enters theirs coordinates.
 *
 * @param row - the y coordinate starting from left top
 * @param column - the x coordinate starting from left top
 * @param level - current level id starting from 0
 * @param rows - amount of rows in the current level
 * @param columns - amount of columns in the current level
 * @param objects - array of objects which are presented in map at the current tick
 *
 * @return action to be executed with the player character - one of UP, LEFT, DOWN, RIGHT, PASS
 */
char script(unsigned row, unsigned column, unsigned level,
            unsigned rows, unsigned columns, const char* objects);
