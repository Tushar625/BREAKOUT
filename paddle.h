#pragma once

class paddle_class
{
public:

	double x, y, dx;

	int size, color;

	paddle_class() : dx(200), x(0), y(0), size(1), color(0)
	{}

	int get_width()
	{
		return (size + 1) * 32;
	}

	int get_height()
	{
		return 16;
	}

	// returns direction of movement

	int update(double dt)
	{
		int dir = 0;

		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Left))
		{
			x -= dx * dt;

			--dir;
		}

		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Right))
		{
			x += dx * dt;

			++dir;
		}

		if (x < 0)
		{
			x = 0;

			dir = 0;
		}

		if (x > VIRTUAL_WIDTH - (size + 1) * 32)
		{
			x = VIRTUAL_WIDTH - (size + 1) * 32;

			dir = 0;
		}

		return dir;
	}

	void render()
	{
		auto& curr_paddle = sprite[PADDLE][size + color * 4];

		curr_paddle.setPosition(sf::Vector2f(x, y));

		bb::WINDOW.draw(curr_paddle);
	}
};