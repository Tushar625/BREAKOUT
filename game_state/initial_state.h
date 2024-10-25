// the initial state of this game

#pragma once

// creating the buttons

class str_button : public BUTTON
{
	sf::Text button_text;

	void ORDINARY_STATE() override
	{
		button_text.setFillColor(sf::Color::White);

		WINDOW.draw(button_text);
	}

	void HOVERING_STATE() override
	{
		button_text.setFillColor(sf::Color::Cyan);

		WINDOW.draw(button_text);
	}

	public:

	str_button(int xin, int yin, std::string button_str)
	{
		button_text = medium_text;	// button text will have sam eproperties as medium text

		button_text.setString(button_str);

		set_height(MEDIUM_FONT_SIZE);

		set_width(button_text.getLocalBounds().width);

		set_pos(xin, yin, BOTTOM_CENTER);

		button_text.setPosition(sf::Vector2f(get_x(), get_y()));
	}
};


class initial_state : public BASE_STATE
{
	str_button quit, high_score, play;

	BUTTON_LIST menu; // the menu to be displayed in this state

	sf::Text breakout;

	sf::Sound sound;

	// pointer for menu as a static member function

	static void pointer(BUTTON_LIST& menu)
	{
		auto button = menu.get_mbutton<str_button>();

		medium_text.setFillColor(sf::Color::Cyan);

		medium_text.setString(">>>");

		medium_text.setPosition(sf::Vector2f(button.get_x() - medium_text.getLocalBounds().width - 20, button.get_y()));

		WINDOW.draw(medium_text);

		medium_text.setString("<<<");

		medium_text.setPosition(sf::Vector2f(button.get_x() + button.get_width() + 20, button.get_y()));

		WINDOW.draw(medium_text);
	}

	public:

	// initialize the buttons and manu

	initial_state() :
		
		quit(VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT - 10, "QUIT"),
		
		high_score(VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT - 40, "HIGH SCORES"),
		
		play(VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT - 70, "START"),

		menu({ &play, &high_score, &quit })

	{
		// prepare the breakout text

		breakout = large_text;

		breakout.setString("BREAKOUT");

		int xout, yout;

		to_top_left(xout, yout, VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2, LARGE_FONT_SIZE, (int)breakout.getLocalBounds().width, CENTER);

		breakout.setPosition(sf::Vector2f(xout, yout - 10));
	}

	private:

	void Enter()
	{
		music.setLoop(true);

		music.play();
	}

	int Update(double dt)
	{
		auto mpos = INPUT.pointer();

		auto sel = menu.Update(
			mpos.x,
			mpos.y,
			INPUT.isPressedM(sf::Mouse::Left),
			INPUT.isReleasedM(sf::Mouse::Left),
			INPUT.isPressed(sf::Keyboard::Scan::Up),
			INPUT.isPressed(sf::Keyboard::Scan::Down),
			INPUT.isPressed(sf::Keyboard::Scan::Enter)
		);

		if (INPUT.isPressed(sf::Keyboard::Scan::Up) || INPUT.isPressed(sf::Keyboard::Scan::Down))
		{
			sound.setBuffer(sound_buffer[SELECT]);

			sound.play();
		}

		if (INPUT.isReleasedM(sf::Mouse::Left) || INPUT.isPressed(sf::Keyboard::Scan::Enter))
		{
			sound.setBuffer(sound_buffer[CONFIRM]);

			sound.play();
		}

		// play = 0, high_score = 1, quit = 2

		if (sel == 0)
		{
			return PLAY;
		}
		
		if (sel == 2)
		{
			return EXIT;
		}

		return -1;
	}

	void Render()
	{
		menu.Render(initial_state::pointer);

		WINDOW.draw(breakout);
	}

	void Exit()
	{
		music.stop();
	}
}initial;