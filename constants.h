
// the constants for this game

#pragma once

#define WINDOW_WIDTH 1280

#define WINDOW_HEIGHT 720

#define VIRTUAL_WIDTH 432

#define VIRTUAL_HEIGHT 243

#define SMALL_FONT_SIZE 8

#define MEDIUM_FONT_SIZE 16

#define LARGE_FONT_SIZE 32

enum TEXTURE_ENUM { BACKGROUND, MAIN, ARROWS, HEARTS, PARTICLE, TEXTURE_COUNT };

enum SOUND_ENUM { PADDLE_HIT, SCORE, WALL_HIT, CONFIRM, SELECT, NO_SELECT, BRICK_HIT_1, BRICK_HIT_2, HURT, VICTORY, RECOVER, HIGH_SCORE, PAUSE, SOUND_COUNT };

enum GAME_STATE_ENUM { INITIAL, GAME_STATE_COUNT, EXIT };