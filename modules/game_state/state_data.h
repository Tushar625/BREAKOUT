#pragma once



// creating the string buttons

class str_button : public bb::BUTTON
{
	sf::Text button_text;

	void ORDINARY_STATE() override
	{
		button_text.setPosition(sf::Vector2f(get_x(), get_y()));

		/*
			by default ordinary button color is white, "button_color"
			is kept to chenge it if needed, here it is used primarily
			by the menu list pointer to indicate which button is selected
		*/

		button_text.setFillColor(button_color);

		bb::WINDOW.draw(button_text);

		button_color = sf::Color::White;
	}

	void HOVERING_STATE() override
	{
		button_text.setPosition(sf::Vector2f(get_x(), get_y()));

		button_text.setFillColor(sf::Color::Cyan);

		bb::WINDOW.draw(button_text);
	}

public:

	sf::Color button_color;

	str_button(int xin, int yin, std::string button_str, bb::COORD_POSITION pos = bb::TOP_LEFT)
	{
		button_text = medium_text;	// button text will have same eproperties as medium text

		button_text.setString(button_str);

		set_height(MEDIUM_FONT_SIZE);

		set_width(button_text.getLocalBounds().width);

		set_pos(xin, yin, pos);

		button_color = sf::Color::White;	// default ordinary state color is white
	}

	// pointer for menu as a static member function

	// >>> button <<<

	static void pointer(bb::BUTTON_LIST& menu)
	{
		str_button& button = menu.get_mbutton<str_button>();

		medium_text.setFillColor(sf::Color::Cyan);

		medium_text.setString(">>>");

		medium_text.setPosition(sf::Vector2f(button.get_x() - medium_text.getLocalBounds().width - 20, button.get_y()));

		bb::WINDOW.draw(medium_text);

		medium_text.setString("<<<");

		medium_text.setPosition(sf::Vector2f(button.get_x() + button.get_width() + 20, button.get_y()));

		bb::WINDOW.draw(medium_text);

		// change the original state color to indicate that it's selected

		button.button_color = sf::Color::Cyan;
	}

	// ----------
	// | button |
	// ----------

	static void box(bb::BUTTON_LIST& menu)
	{
		str_button& button = menu.get_mbutton<str_button>();

		// the text seems to have 6 pixels of padding on the top so we add 6 to the height instead of 12

		sf::RectangleShape box(sf::Vector2f(button.get_width() + 12, button.get_height() + 6));

		box.setPosition(sf::Vector2f(button.get_x() - 6, button.get_y()));

		box.setOutlineThickness(1);

		box.setOutlineColor(sf::Color::Cyan);

		box.setFillColor(sf::Color::Transparent);

		bb::WINDOW.draw(box);

		// change the original state color to indicate that it's selected

		button.button_color = sf::Color::Cyan;
	}
};



// to hold general game data that will be used by every state

struct game_data_type
{
	int level;

	int highest_score;

	int score_till_last_level;

	int health;

	/*
		data of this structure is stored in AppData\Local\Breakout\data.bin
	*/

	game_data_type() : level(0), highest_score(0), score_till_last_level(0), health(MAX_HEALTH)
	{
		bb::load_local_appdata("Breakout\\data.bin", *this);
	}

	~game_data_type()
	{
		bb::store_local_appdata("Breakout\\data.bin", *this);
	}

	// after game is over this functon is used to reset the general game data

	void reset(int current_level_score)
	{
		int total_score = score_till_last_level + current_level_score;

		level = 0;

		score_till_last_level = 0;

		health = MAX_HEALTH;

		if (total_score > highest_score)
		{
			// new highest score

			sf::Sound sound;

			sound.setBuffer(sound_buffer[HIGH_SCORE]);

			sound.play();

			highest_score = total_score;
		}
	}

	// change the general game data to reach next level

	void next_level(int current_level_score)
	{
		level += 1;

		score_till_last_level += current_level_score;

		if (health < MAX_HEALTH)
		{
			health += 1;
		}
	}
};



struct level_data_type
{
	ball_class ball;

	paddle_class paddle;

	BrickMap bricks;

	bb::Firecracker explo;

	int current_level_score;

	level_data_type() : current_level_score(0)
	{}

	// sets a new level

	void start_level(int level)
	{
		bricks.level_maker(level);

		current_level_score = 0;
	}

	// brick array is cleared after a level is finished

	bool is_new_level() const
	{
		return bricks.empty();
	}

	void end_level()
	{
		bricks.clear();
	}

	// render the bricks in this level

	void render_bricks_explosions()
	{
		bb::WINDOW.draw(explo);

		bb::WINDOW.draw(bricks);
	}

	bool all_bricks_explosions_finished()
	{
		return bricks.empty() && explo.empty();
	}
};