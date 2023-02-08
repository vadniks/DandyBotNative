/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

#include "consts.hpp"

unsigned APP_WIDTH = 1366;
unsigned APP_HEIGHT = 768;
c_str APP_NAME = "DandyBotNative";
c_str APP_ICON = ":/dandyBot_block.png";
c_str START_GAME = "Start the game";
c_str GAME_DATA = ":/gameData.json";
c_str LEVELS = "levels";
c_str MAP = "map";
c_str START = "start";
c_str STEPS = "steps";
c_str MAPS = "maps";
const char EMPTY_OBJ = ' ';
const char BLOC_OBJ = '#';
const char COIN_MIN_OBJ = '1';
const char COIN_MAX_OBJ = '9';
const char ENEMY_MIN_OBJ = 'a';
const char ENEMY_MAX_OBJ = 'f';
const char PLAYER_OBJ = '!';
unsigned GAME_OBJECT_SIZE = 30;
c_str EMPTY_ICON = ":/dandyBot_empty.png";
c_str BLOC_ICON = APP_ICON;
c_str COIN_ICON = ":/dandyBot_coin.png";
c_str ENEMY_ICON_PREFIX = ":/dandyBot_enemy_";
c_str ICON_SUFFIX = ".png";
c_str PLAYER_ICON = ":/dandyBot_player.png";
c_str YOU_WON = "You has won";
c_str PLAYER_SCORE = "Player score";
c_str CURRENT_LEVEL = "Current level";
unsigned TICK_INTERVAL = 25;
float BOT_MOVE_CHANCE = 0.05;
