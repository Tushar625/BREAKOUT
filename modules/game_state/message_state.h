
// the message state of this game, displays the victory and defeat message

#pragma once



class message_state : public bb::BASE_STATE
{
	/*
		a structure nicely encaptulate the data (buttons and text messages)
		used in this state locally
	*/

	struct data
	{
		std::array<str_button, 2> button_arr;

		bb::BUTTON_LIST menu;	// the menu to be displayed in this state

		sf::Text main_message_text, score_text, complimentary_message_text;

		data(const std::string& main_message, const std::string& complimentary_message, const std::string& next_button_text, int score) :
			button_arr{
				str_button(0, 0, next_button_text),
				str_button(0, 0, "HOME")
			},
			menu({ &button_arr[0], &button_arr[1] })
		{
			// main text

			main_message_text = large_text;

			main_message_text.setString(main_message);

			int xout, yout, boxh = VIRTUAL_HEIGHT / 1.7;

			/*
				imagine a box placed in the center of the screen with height
				boxh and width same as main message

				xout and yout represents the top left point this box
			*/

			bb::to_top_left(
				xout, yout,
				VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2,
				boxh, (int)main_message_text.getLocalBounds().width,
				bb::CENTER
			);

			// place the main message in the box, touching its top border

			main_message_text.setPosition(sf::Vector2f(xout, yout));

			// score

			score_text = medium_text;

			score_text.setFillColor(sf::Color::White);

			score_text.setString(std::to_string(score));

			int tempx, tempy;

			// place the center of score text 10 pixels up the center of the box

			bb::to_top_left(
				tempx, tempy,
				VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2 - 10,
				MEDIUM_FONT_SIZE, (int)score_text.getLocalBounds().width,
				bb::CENTER
			);

			score_text.setPosition(sf::Vector2f(tempx, tempy));

			// cmp text

			complimentary_message_text = medium_text;

			complimentary_message_text.setFillColor(sf::Color::White);

			complimentary_message_text.setString(complimentary_message);

			// place the center of comp message 10 pixels down the center of the box

			bb::to_top_left(
				tempx, tempy,
				VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2 + 10,
				MEDIUM_FONT_SIZE, (int)complimentary_message_text.getLocalBounds().width,
				bb::CENTER
			);

			complimentary_message_text.setPosition(sf::Vector2f(tempx, tempy));

			// buttons

			/*
				bottom of the buttons are at the same level as the bottom of the box
				they are placed 90 pixels away from the sides
			*/

			menu[0].set_pos(90, yout + boxh, bb::BOTTOM_LEFT);

			menu[1].set_pos(VIRTUAL_WIDTH - 90, yout + boxh, bb::BOTTOM_RIGHT);

			/*
			                                  Screen Width
				|----------------------------------------------------------------------| -
			                                                                             |
			                                                                             |
									|=========MAIN MESSAGE=========|                     |
									|                              |                     |
									|                              |                     |
									|                              |                     |
									|          SCORE TEXT          |                     |
									|                              |                     | Screen Height
									|         COMP MESSAGE         |                     |
									|                              |                     |
									|                              |                     |
						BUTTON1     |______________________________|     BUTTON2         |
											                                             |
																						 |
																						 -
			*/
		}
	};

	std::unique_ptr<data> b_data;


	public:


	// the data this state receives from play state

	std::string main_message, complimentary_message, next_button_text;

	int score;

	message_state() : score(0)
	{}

	// following function is used to send data to message state state

	void init(const std::string& _main_message, const std::string& _complimentary_message, const std::string& _next_button_text, int _score)
	{
		main_message = _main_message;

		complimentary_message = _complimentary_message;

		next_button_text = _next_button_text;

		score = _score;
	}


	private:


	sf::Sound sound;


	void Enter()
	{
		// creating the local state data

		b_data = std::make_unique<data>(main_message, complimentary_message, next_button_text, score);	// creating the data used in this state

		// following strings are not necessary anymore as the sf::Text objects are created

		main_message.clear();

		complimentary_message.clear();

		next_button_text.clear();
	}


	void Update(double dt)
	{
		auto mpos = bb::INPUT.pointer();

		auto sel = b_data->menu.Update(
			mpos.x,
			mpos.y,
			bb::INPUT.isPressedM(sf::Mouse::Left),
			bb::INPUT.isReleasedM(sf::Mouse::Left),
			bb::INPUT.isPressed(sf::Keyboard::Scan::Left),
			bb::INPUT.isPressed(sf::Keyboard::Scan::Right),
			bb::INPUT.isPressed(sf::Keyboard::Scan::Enter)
		);

		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Left) || bb::INPUT.isPressed(sf::Keyboard::Scan::Right))
		{
			sound.setBuffer(sound_buffer[SELECT]);

			sound.play();
		}

		if ((bb::INPUT.isReleasedM(sf::Mouse::Left) || bb::INPUT.isPressed(sf::Keyboard::Scan::Enter)) && sel != -1)
		{
			sound.setBuffer(sound_buffer[CONFIRM]);

			sound.play();
		}

		if (sel == 0)
		{
			game_state.change_to(serve);
		}

		if (sel == 1)
		{
			game_state.change_to(initial);
		}
	}


	void Render()
	{
		// render the buttons and the messages

		b_data->menu.Render(str_button::box);

		bb::WINDOW.draw(b_data->main_message_text);

		bb::WINDOW.draw(b_data->score_text);

		bb::WINDOW.draw(b_data->complimentary_message_text);
	}


	void Exit()
	{
		b_data.reset();	// delete the local state data
	}

}message;