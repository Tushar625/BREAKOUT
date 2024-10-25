
#define SET_ANTIALIASHING	// this macro allows you to set antialiashing

#include"requirements.h"

// the value returned by this function will be set as the value for antialiashing

unsigned int set_antialiashing()
{
	return 0;
}

// loading the game states into the state machine

STATE_MACHINE game_state({ &initial, &play });

inline bool Game::Create()
{
	// setting window title


	WINDOW.setTitle("Breakout prototype 2");

	
	// setting window size


	WINDOW.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));

	auto this_view = WINDOW.getView();

	this_view.reset(sf::FloatRect(0, 0, VIRTUAL_WIDTH, VIRTUAL_HEIGHT));

	WINDOW.setView(this_view);


	// other settings


	srand(time(0));

	MY_GAME.set_fps(30);

	game_state.change_to(INITIAL);

	

	//text.setFillColor(sf::Color::White);

	// ~~~~ [write your statements here] ~~~~

	return SUCCESS;
}

inline bool Game::Update(double dt)
{
	// exit

	if (INPUT.isClosed() || INPUT.isPressed(sf::Keyboard::Scan::Escape) || game_state.Update(dt) == EXIT)
		return STOP_GAME_LOOP;

	/*auto pos = INPUT.pointer();

	if(INPUT.isPressedM(sf::Mouse::Left))
	{
		std::cout << "{" << pos.x << ", " << pos.y << "}\n";
	}*/

	return !STOP_GAME_LOOP;
}

inline void Game::Render()
{
	sf::Sprite bg_sprite;

	bg_sprite.setTexture(texture[BACKGROUND]);

	auto bg_size = texture[BACKGROUND].getSize();

	bg_sprite.setScale(sf::Vector2f(VIRTUAL_WIDTH / (float)(bg_size.x - 1), VIRTUAL_HEIGHT / (float)(bg_size.y - 1)));

	WINDOW.draw(bg_sprite);

	game_state.Render();

	small_text.setString(std::to_string(MY_GAME.get_fps()));

	WINDOW.draw(small_text);
}