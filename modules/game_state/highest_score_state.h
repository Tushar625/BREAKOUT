
// the highest score state of this game, displays the highest score ever achieved

#pragma once



class highest_score_state : public bb::BASE_STATE
{
	/*
		a structure nicely encaptulate the data (buttons and text messages)
		used in this state locally
	*/

	struct data
	{
		std::array<str_button, 1> button_arr;

		bb::BUTTON_LIST menu;	// the menu to be displayed in this state

		sf::Text main_message_text, score_text;

		data(int score) :
			button_arr{
				str_button(0, 0, "HOME")
			},
			menu({ &button_arr[0] })
		{
			// main text

			main_message_text = large_text;

			main_message_text.setString("HIGHEST SCORE");

			/*
				imagine a box placed in the center of the screen with height
				boxh and width same as main message

				xout and yout represents the top left point this box
			*/

			int xout, yout, boxh = VIRTUAL_HEIGHT / 1.7;

			bb::to_top_left(xout, yout, VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2, boxh, (int)main_message_text.getLocalBounds().width, bb::CENTER);

			// place the main message in the box, touching its top border

			main_message_text.setPosition(sf::Vector2f(xout, yout));

			// score

			score_text = medium_text;

			score_text.setFillColor(sf::Color::White);

			score_text.setString(std::to_string(score));

			int tempx, tempy;

			// place the center of score text at the center of the box

			bb::to_top_left(
				tempx,
				tempy,
				VIRTUAL_WIDTH / 2,
				VIRTUAL_HEIGHT / 2 + 5,
				MEDIUM_FONT_SIZE,
				(int)score_text.getLocalBounds().width,
				bb::CENTER
			);

			score_text.setPosition(sf::Vector2f(tempx, tempy));

			// buttons

			/*
				bottom of the button is at the same level as the bottom of the box
				and it is placed in the middle of the screen
			*/

			menu[0].set_pos(VIRTUAL_WIDTH / 2, yout + boxh, bb::BOTTOM_CENTER);

			/*
											  Screen Width
				|----------------------------------------------------------------------| -
																						 |
																						 |
									|=========MAIN MESSAGE=========|                     |
									|                              |                     |
									|                              |                     |
									|                              |                     |
									|                              |                     |
									|          SCORE TEXT          |                     | Screen Height
									|                              |                     |
									|                              |                     |
									|                              |                     |
						            |____________BUTTON____________|                     |
																						 |
																						 |
																						 -
			*/
		}
	} *b_data;


	public:


	// data received from the initial state

	int score;

	highest_score_state() : b_data(nullptr), score(0)
	{}

	// following functions are used to send data to this state from initial states

	void init(int _score)
	{
		score = _score;
	}

	private:


	sf::Sound sound;


	void Enter()
	{
		b_data = new data(score);	// creating the local state data
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
			game_state.change_to(initial);
		}
	}


	void Render()
	{
		b_data->menu.Render(str_button::box);

		bb::WINDOW.draw(b_data->main_message_text);

		bb::WINDOW.draw(b_data->score_text);
	}


	void Exit()
	{
		delete b_data;	// destroying the local state data
	}

}highest_score;