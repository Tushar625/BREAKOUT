// the initial state of this game

#pragma once



class message_state : public bb::BASE_STATE
{
	/*
		this demonstrate how nicely we can allocate(during entry) and deallcate(during exit)
		state data
	*/


	// a structure nicely encaptulate the data used in this state locally

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

			/*
				imagine a box placed in the center of the screen with height
				VIRTUAL_HEIGHT / 2 and width same as main message
			*/

			int xout, yout, boxh = VIRTUAL_HEIGHT / 1.7;

			bb::to_top_left(xout, yout, VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2, boxh, (int)main_message_text.getLocalBounds().width, bb::CENTER);

			main_message_text.setPosition(sf::Vector2f(xout, yout));

			// score

			score_text = medium_text;

			score_text.setFillColor(sf::Color::White);

			score_text.setString(std::to_string(score));

			int tempx, tempy;

			bb::to_top_left(
				tempx,
				tempy,
				VIRTUAL_WIDTH / 2,
				VIRTUAL_HEIGHT / 2 - 10,
				MEDIUM_FONT_SIZE,
				(int)score_text.getLocalBounds().width,
				bb::CENTER
			);

			score_text.setPosition(sf::Vector2f(tempx, tempy));

			// cmp text

			complimentary_message_text = medium_text;

			complimentary_message_text.setFillColor(sf::Color::White);

			complimentary_message_text.setString(complimentary_message);

			bb::to_top_left(
				tempx,
				tempy,
				VIRTUAL_WIDTH / 2,
				VIRTUAL_HEIGHT / 2 + 10,
				MEDIUM_FONT_SIZE,
				(int)complimentary_message_text.getLocalBounds().width,
				bb::CENTER
			);

			complimentary_message_text.setPosition(sf::Vector2f(tempx, tempy));

			// buttons

			menu[0].set_pos(90, yout + boxh, bb::BOTTOM_LEFT);

			menu[1].set_pos(VIRTUAL_WIDTH - 90, yout + boxh, bb::BOTTOM_RIGHT);
		}
	} *b_data;


	public:


	std::string main_message, complimentary_message, next_button_text;

	int score;


	private:


	sf::Sound sound;


	void Enter()
	{
		b_data = new data(main_message, complimentary_message, next_button_text, score);	// creating the data used in this state

		main_message.clear();

		complimentary_message.clear();

		next_button_text.clear();
	}


	int Update(double dt)
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

		return -1;
	}


	void Render()
	{
		b_data->menu.Render(str_button::box);

		bb::WINDOW.draw(b_data->main_message_text);

		bb::WINDOW.draw(b_data->score_text);

		bb::WINDOW.draw(b_data->complimentary_message_text);
	}


	void Exit()
	{
		delete b_data;	// delete the data of this state
	}

}message;

// following functions are used to send data to serve state from other states

void set_message_state(const std::string& main_message, const std::string& complimentary_message, const std::string& next_button_text, int score)
{
	message.main_message = main_message;

	message.complimentary_message = complimentary_message;

	message.next_button_text = next_button_text;

	message.score = score;
}