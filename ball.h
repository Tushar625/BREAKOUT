#pragma once

class ball_class
{
	double x, y;

	int width, height, index;

	sf::Sound snd;

public:

	double dx, dy;

	ball_class()
	{
		x = y = dx = dy = 0;

		width = height = 8;

		index = 0;
	}

	void reset(int ball_type = 0)
	{
		dx = dy = -100;

		// place the ball on the paddle
		
		x = paddle.x + paddle.get_width() / 2.0;
			
		y = paddle.y - height - 1;

		index = ball_type;
	}

	bool collids(double xb, double yb, int widthb, int heightb)
	{
		// if top of any of the boxes below the bottom of others

		if (/* top */ y + height < yb || /* bottom */ yb + heightb < y)
		{
			return false;
		}

		// if left of any of the boxes after the right of others

		if (/* left */ x + width < xb || /* right */ xb + widthb < x)
		{
			return false;
		}

		return true;
	}

	void update(double dt)
	{
		x += dx * dt;

		y += dy * dt;

		// top collision

		if (y < 0)
		{
			y = 0;

			dy = -dy;

			snd.setBuffer(sound_buffer[WALL_HIT]);

			snd.play();
		}

		// left collision

		if (x < 0)
		{
			x = 0;

			dx = -dx;

			snd.setBuffer(sound_buffer[WALL_HIT]);

			snd.play();
		}

		// right collision

		if (x + width > VIRTUAL_WIDTH)
		{
			x = VIRTUAL_WIDTH - width;

			dx = -dx;

			snd.setBuffer(sound_buffer[WALL_HIT]);

			snd.play();
		}
	}

	void render()
	{
		sprite[BALL][index].setPosition(sf::Vector2f(x, y));

		WINDOW.draw(sprite[BALL][index]);
	}
} ball;