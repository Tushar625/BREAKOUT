#pragma once



// creating the buttons

class str_button : public bb::BUTTON
{
	sf::Text button_text;

	void ORDINARY_STATE() override
	{
		button_text.setFillColor(button_color);

		bb::WINDOW.draw(button_text);

		button_color = sf::Color::White;
	}

	void HOVERING_STATE() override
	{
		button_text.setFillColor(sf::Color::Cyan);

		bb::WINDOW.draw(button_text);
	}

public:

	sf::Color button_color;

	str_button(int xin, int yin, std::string button_str)
	{
		button_text = medium_text;	// button text will have sam eproperties as medium text

		button_text.setString(button_str);

		set_height(MEDIUM_FONT_SIZE);

		set_width(button_text.getLocalBounds().width);

		set_pos(xin, yin, bb::BOTTOM_CENTER);

		button_text.setPosition(sf::Vector2f(get_x(), get_y()));

		button_color = sf::Color::White;
	}

	// pointer for menu as a static member function

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

	game_data_type()
	{
		// try to load these data from a file

		level = 0;

		highest_score = 0;

		score_till_last_level = 0;

		health = MAX_HEALTH;
	}

	~game_data_type()
	{
		// load this data back into a file
	}

	void reset()
	{
		level = 0;

		score_till_last_level = 0;

		health = MAX_HEALTH;
	}
};



struct level_data_type
{
	ball_class ball;

	paddle_class paddle;

	BrickMap bricks;

	bb::Firecracker explo;

	int current_level_score;

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

	bool all_bricks_explosions_left()
	{
		return bricks.empty() && explo.empty();
	}
};