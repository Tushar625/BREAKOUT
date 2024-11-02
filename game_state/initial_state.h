// the initial state of this game

#pragma once



extern class serve_state serve;

void set_serve_state(game_data_type* i_data);



class initial_state : public bb::BASE_STATE
{
	/*
		this demonstrate how nicely we can allocate(during entry) and deallcate(during exit)
		state data 
	*/
	

	// a structure nicely encaptulate the data used in this state locally

	struct data
	{
		std::array<str_button, 3> button_arr;

		bb::BUTTON_LIST menu;	// the menu to be displayed in this state

		sf::Text breakout;

		data() :
			button_arr{
				str_button(VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT - 70, "START"),
				str_button(VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT - 40, "HIGH SCORES"),
				str_button(VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT - 10, "QUIT")
			},
			menu({ &button_arr[0], &button_arr[1], &button_arr[2] })
		{
			breakout = large_text;

			breakout.setString("BREAKOUT");

			int xout, yout;

			bb::to_top_left(xout, yout, VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2, LARGE_FONT_SIZE, (int)breakout.getLocalBounds().width, bb::CENTER);

			breakout.setPosition(sf::Vector2f(xout, yout - 10));
		}
	} *b_data;


	sf::Sound sound;

	game_data_type i_data;	// created to hold general game data


	void Enter()
	{
		b_data = new data();	// creating the data used in this state

		music.setLoop(true);

		music.play();
	}


	int Update(double dt)
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
			set_serve_state(&i_data);	// sending data to serve state

			game_state.change_to(serve);
		}
		
		if (sel == 2)
		{
			return EXIT_CODE;
		}

		return -1;
	}


	void Render()
	{
		b_data->menu.Render(str_button::pointer);

		bb::WINDOW.draw(b_data->breakout);
	}


	void Exit()
	{
		delete b_data;	// delete the data of this state

		music.stop();
	}

}initial;