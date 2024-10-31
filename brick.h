#pragma once

class brick_class
{
	bool invisible;

public:

	double x, y;

	int color, tier;

	brick_class() : x(0), y(0), color(0), tier(0), invisible(false)
	{}

	brick_class(double xin, double yin, int color_in, int tier_in) : x(xin), y(yin), color(color_in), tier(tier_in), invisible(false)
	{}

	int get_width()
	{
		return 32;
	}

	int get_height()
	{
		return 16;
	}

	void hit()
	{
		invisible = true;
	}

	bool is_visible()
	{
		return !invisible;
	}

	void render()
	{
		if (invisible)
			return;

		auto& curr_brick = sprite[BRICK][tier + color * 4];

		curr_brick.setPosition(sf::Vector2f(x, y));

		bb::WINDOW.draw(curr_brick);
	}
};