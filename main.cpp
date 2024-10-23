
/*
	a general format only, you should remove or change any code as you need
*/

#define SET_ANTIALIASHING	// this macro allows you to set antialiashing

#include"game.h"	// mention path to game.h

#include<iostream>	// only for debugging

#include<string>

#define HEIGHT 600

#define WIDTH 800

// the value returned by this function will be set as the value for antialiashing

unsigned int set_antialiashing()
{
	return 8;
}

sf::Font font;

sf::Text text;

// ~~~~ [write your statements (extra functions, classes, variables) here] ~~~~

inline bool Game::Create()
{
	WINDOW.setSize(sf::Vector2u(WIDTH, HEIGHT));

	srand(time(0));

	MY_GAME.set_fps(30);

	 WINDOW.setTitle("Breakout prototype 1");

	if (!font.loadFromFile("font/font.ttf"))
	{
		std::cout << "can't load font\n";
	}

	text.setFont(font);

	text.setCharacterSize(20);

	text.setFillColor(sf::Color::White);

	// ~~~~ [write your statements here] ~~~~

	return SUCCESS;
}

inline bool Game::Update(double dt)
{
	// exit

	if (INPUT.isClosed() || INPUT.isPressed(sf::Keyboard::Scan::Escape))
		return STOP_GAME_LOOP;

	// ~~~~ [write your statements here] ~~~~

	return !STOP_GAME_LOOP;
}

inline void Game::Render()
{
	text.setString("Fps: " + std::to_string(MY_GAME.get_fps()));

	WINDOW.draw(text);

	// ~~~~ [write your statements here] ~~~~
}