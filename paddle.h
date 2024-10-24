#pragma once

class paddle_class
{
	public:

	double x, y, dx;

	int size, color;

	paddle_class() : dx(200), x(0), y(0), size(1), color(0)
	{}

	void update(double dt)
	{
		if (INPUT.isHeld(sf::Keyboard::Scan::Left))
		{
			x -= dx * dt;
		}

		if (INPUT.isHeld(sf::Keyboard::Scan::Right))
		{
			x += dx * dt;
		}

		if (x < 0)
		{
			x = 0;
		}

		if (x > VIRTUAL_WIDTH - (size + 1) * 32)
		{
			x = VIRTUAL_WIDTH - (size + 1) * 32;
		}
	}

	void render()
	{
		auto& curr_paddle = sprite[PADDLE][size + color * 4];

		curr_paddle.setPosition(sf::Vector2f(x, y));

		WINDOW.draw(curr_paddle);
	}
} paddle;