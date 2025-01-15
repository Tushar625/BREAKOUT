
// the initial state of this game home of the game

#pragma once



extern class serve_state serve;



extern class highest_score_state highest_score;



class initial_state : public bb::BASE_STATE
{
	/*
		a structure nicely encaptulate the data (buttons and text messages)
		used in this state locally
	*/

	struct data
	{
		std::array<str_button, 3> button_arr;

		bb::BUTTON_LIST menu;	// the menu to be displayed in this state

		sf::Text breakout;

		data() :
			button_arr{
				str_button(VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT - 70, "START", bb::BOTTOM_CENTER),
				str_button(VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT - 40, "HIGHEST SCORE", bb::BOTTOM_CENTER),
				str_button(VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT - 10, "QUIT", bb::BOTTOM_CENTER)
		},
			menu({ &button_arr[0], &button_arr[1], &button_arr[2] })
		{
			breakout = large_text;

			breakout.setString("BREAKOUT");

			int xout, yout;

			// place the center of breakout text in the center of the screen

			bb::to_top_left(xout, yout, VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2, LARGE_FONT_SIZE, (int)breakout.getLocalBounds().width, bb::CENTER);

			breakout.setPosition(sf::Vector2f(xout, yout - 10));
		}
	};
	
	std::unique_ptr<data> b_data;

public:

	initial_state()
	{}

private:

	sf::Sound sound;

	game_data_type i_data;	// created to hold general game data


	void Enter()
	{
		b_data = std::make_unique<data>();	// creating the local state data

		music.setLoop(true);

		music.play();
	}


	void Update(double dt)
	{
		auto mpos = bb::INPUT.pointer();

		auto sel = b_data->menu.Update(
			mpos.x,
			mpos.y,
			bb::INPUT.isPressedM(sf::Mouse::Left),
			bb::INPUT.isReleasedM(sf::Mouse::Left),
			bb::INPUT.isPressed(sf::Keyboard::Scan::Up),
			bb::INPUT.isPressed(sf::Keyboard::Scan::Down),
			bb::INPUT.isPressed(sf::Keyboard::Scan::Enter)
		);

		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Up) || bb::INPUT.isPressed(sf::Keyboard::Scan::Down))
		{
			sound.setBuffer(sound_buffer[SELECT]);

			sound.play();
		}

		if ((bb::INPUT.isReleasedM(sf::Mouse::Left) || bb::INPUT.isPressed(sf::Keyboard::Scan::Enter)) && sel != -1)
		{
			sound.setBuffer(sound_buffer[CONFIRM]);

			sound.play();
		}

		// play = 0, high_score = 1, quit = 2

		if (sel == 0)
		{
			game_state.change_to(serve, &i_data);
		}

		if (sel == 1)
		{
			game_state.change_to(highest_score, i_data.highest_score);
		}
		
		if (sel == 2 || bb::INPUT.isPressed(sf::Keyboard::Scan::Escape))
		{
			game_state.change_to(bb::NULL_STATE);
		}
	}


	void Render()
	{
		b_data->menu.Render(str_button::pointer);

		bb::WINDOW.draw(b_data->breakout);
	}


	void Exit()
	{
		b_data.reset();	// destroying the local state data

		music.stop();
	}

}initial;