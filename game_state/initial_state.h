// the initial state of this game

#pragma once

#include<array>

extern class play_state play;

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
	/*
		this demonstrate how nicely we can allocate(during entry) and deallcate(during exit)
		state data 
	*/
	
	// a structure nicely encaptulate the data used in this state locally

	struct data
	{
		std::array<str_button, 3> button_arr;

		BUTTON_LIST menu;	// the menu to be displayed in this state

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

			to_top_left(xout, yout, VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2, LARGE_FONT_SIZE, (int)breakout.getLocalBounds().width, CENTER);

			breakout.setPosition(sf::Vector2f(xout, yout - 10));
		}
	} *pdata;

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

	sf::Sound sound;

	void Enter()
	{
		pdata = new data();	// creating the data used in this state

		music.setLoop(true);

		music.play();
	}

	int Update(double dt)
	{
		auto mpos = INPUT.pointer();

		auto sel = pdata->menu.Update(
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

		if ((INPUT.isReleasedM(sf::Mouse::Left) || INPUT.isPressed(sf::Keyboard::Scan::Enter)) && sel != -1) 
		{
			sound.setBuffer(sound_buffer[CONFIRM]);

			sound.play();
		}

		// play = 0, high_score = 1, quit = 2

		if (sel == 0)
		{
			game_state.change_to(play);
		}
		
		if (sel == 2)
		{
			return EXIT_CODE;
		}

		return -1;
	}

	void Render()
	{
		pdata->menu.Render(initial_state::pointer);

		WINDOW.draw(pdata->breakout);
	}

	void Exit()
	{
		delete pdata;	// delete the data of this state

		music.stop();
	}
}initial;