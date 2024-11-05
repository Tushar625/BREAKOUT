
#ifdef NDEBUG

// this is to create an windows application in release mode

#define USE_MAIN WinMain

#endif

#define SET_ANTIALIASHING	// this macro allows you to set antialiashing

#define GAME_CLEAR

#include"requirements/requirements.h"



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

	if (bb::INPUT.isClosed() || game_state.Update(dt) == EXIT_CODE)
		return STOP_GAME_LOOP;

	/*auto pos = INPUT.pointer();

	if(INPUT.isPressedM(sf::Mouse::Left))
	{
		std::cout << "{" << pos.x << ", " << pos.y << "}\n";
	}*/

	return !STOP_GAME_LOOP;
}



inline void bb::Game::Clear()
{
	bb::WINDOW.draw(bg_sprite);
}



inline void bb::Game::Render()
{
	game_state.Render();

	small_text.setString(std::to_string(static_cast<int>(bb::MY_GAME.get_fps() + .5)));

	bb::WINDOW.draw(small_text);
}