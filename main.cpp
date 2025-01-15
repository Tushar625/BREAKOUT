


#define SET_ANTIALIASHING	// this macro allows you to set antialiashing

#define GAME_CLEAR

//#define MSVC_DETECT_MEMORY_LEAK

#include"modules/requirements.h"



// the value returned by this function will be set as the value for antialiashing

unsigned int bb::set_antialiashing()
{
	return 0;
}



inline bool bb::Game::Create()
{
	// setting window title


	bb::WINDOW.setTitle("Breakout");

	
	// setting window size


	bb::WINDOW.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));

	sf::View this_view = bb::WINDOW.getView();

	this_view.reset(sf::FloatRect(0, 0, VIRTUAL_WIDTH, VIRTUAL_HEIGHT));

	bb::WINDOW.setView(this_view);


	// other settings

	bb::WINDOW.setPosition(sf::Vector2i(100, 100));
	
	srand(time(0));

	bb::MY_GAME.set_fps(60);

	game_state.change_to(initial);


	return SUCCESS;
}



inline bool bb::Game::Update(double dt)
{
	// exit

	if (bb::INPUT.isClosed() || game_state.null_state())
		return STOP_GAME_LOOP;

	game_state.Update(dt);

	return !STOP_GAME_LOOP;
}



inline void bb::Game::Clear()
{
	bb::WINDOW.draw(bg_sprite);
}



inline void bb::Game::Render()
{
	game_state.Render();

	//render fps

	small_text.setString(std::to_string(static_cast<int>(bb::MY_GAME.get_fps() + .5)));

	bb::WINDOW.draw(small_text);
}