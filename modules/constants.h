
// the constants for this game

#pragma once

#define WINDOW_WIDTH 1280

#define WINDOW_HEIGHT 720

#define VIRTUAL_WIDTH 432

#define VIRTUAL_HEIGHT 243

#define SMALL_FONT_SIZE 8

#define MEDIUM_FONT_SIZE 16

#define LARGE_FONT_SIZE 32

#define MAX_HEALTH 3

enum TEXTURE_ENUM { BACKGROUND, MAIN, TEXTURE_COUNT };

enum SPRITE_ENUM { PADDLE, BALL, HEART, SPRITE_COUNT };

enum SOUND_ENUM { PADDLE_HIT, SCORE, WALL_HIT, CONFIRM, SELECT, NO_SELECT, BRICK_HIT_1, BRICK_HIT_2, HURT, VICTORY, RECOVER, HIGH_SCORE, PAUSE, SOUND_COUNT };

const std::array<sf::Color, 5> BRICK_COLOR{
	sf::Color(99, 155, 255),
	sf::Color(106, 190, 48),
	sf::Color(217, 87, 99),
	sf::Color(215, 123, 186),
	sf::Color(251, 242, 54)
};

//const std::array<sf::Color, 5> BRICK_COLOR{
//	sf::Color(91, 110, 255),
//	sf::Color(75, 105, 47),
//	sf::Color(172, 50, 50),
//	sf::Color(118, 66, 138),
//	sf::Color(223, 113, 38)
//};