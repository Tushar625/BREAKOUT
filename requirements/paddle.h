#pragma once

class paddle_class
{
public:

	/*
		we keep these parameters public so that they can be changed
		later to create different effects
	*/

	double x, y, dx;

	int size, color;

	paddle_class() : dx(200), x(0), y(0), size(1), color(0)
	{}

	int get_width() const
	{
		return (size + 1) * 32;
	}

	int get_height() const
	{
		return 16;
	}

	// returns direction of movement -1 left, 1 right, 0 no change

	int update(double dt)
	{
		int dir = 0;

		// go left

		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Left))
		{
			x -= dx * dt;

			--dir;
		}

		// go right

		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Right))
		{
			x += dx * dt;

			++dir;
		}

		// touching left border

		if (x < 0)
		{
			x = 0;

			dir = 0;
		}

		// touching right border

		if (x > VIRTUAL_WIDTH - (size + 1) * 32)
		{
			x = VIRTUAL_WIDTH - (size + 1) * 32;

			dir = 0;
		}

		return dir;
	}

	void render() const
	{
		// getting the poper paddle sprite according to size and color

		auto& curr_paddle = sprite[PADDLE][size + color * 4];

		curr_paddle.setPosition(sf::Vector2f(x, y));

		bb::WINDOW.draw(curr_paddle);
	}
};