
#define SET_ANTIALIASHING	// this macro allows you to set antialiashing

#include"requirements.h"

// the value returned by this function will be set as the value for antialiashing

unsigned int bb::set_antialiashing()
{
	return 0;
}

inline bool bb::Game::Create()
{
	// setting window title


	bb::WINDOW.setTitle("Breakout prototype 3");

	
	// setting window size


	bb::WINDOW.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));

	auto this_view = bb::WINDOW.getView();

	this_view.reset(sf::FloatRect(0, 0, VIRTUAL_WIDTH, VIRTUAL_HEIGHT));

	bb::WINDOW.setView(this_view);


	// other settings

	bb::WINDOW.setPosition(sf::Vector2i(100, 100));
	
	srand(time(0));

	bb::MY_GAME.set_fps(30);

	game_state.change_to(initial);

	

	//text.setFillColor(sf::Color::White);

	// ~~~~ [write your statements here] ~~~~

	return SUCCESS;
}

inline bool bb::Game::Update(double dt)
{
	// exit

	if (bb::INPUT.isClosed() || bb::INPUT.isPressed(sf::Keyboard::Scan::Escape) || game_state.Update(dt) == EXIT_CODE)
		return STOP_GAME_LOOP;

	/*auto pos = INPUT.pointer();

	if(INPUT.isPressedM(sf::Mouse::Left))
	{
		std::cout << "{" << pos.x << ", " << pos.y << "}\n";
	}*/

	return !STOP_GAME_LOOP;
}

inline void bb::Game::Render()
{
	sf::Sprite bg_sprite;

	bg_sprite.setTexture(texture[BACKGROUND]);

	auto bg_size = texture[BACKGROUND].getSize();

	bg_sprite.setScale(sf::Vector2f(VIRTUAL_WIDTH / (float)(bg_size.x - 1), VIRTUAL_HEIGHT / (float)(bg_size.y - 1)));

	bb::WINDOW.draw(bg_sprite);

	game_state.Render();

	small_text.setString(std::to_string(static_cast<int>(bb::MY_GAME.get_fps() + .5)));

	bb::WINDOW.draw(small_text);
}