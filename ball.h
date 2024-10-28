#pragma once

class ball_class
{
	sf::Sound snd;

	int width, height;

public:

	double x, y, dx, dy;

	int index;

	ball_class()
	{
		x = y = dx = dy = 0;

		width = height = 8;

		index = 0;
	}

	int get_width() const
	{
		return width;
	}

	int get_height() const
	{
		return height;
	}

	void reset(int ball_type = 0)
	{
		dx = (100 + rand() % 51) * (rand() % 2 ? -1 : 1);
		
		dy = (100 + rand() % 51) * (rand() % 2 ? -1 : 1);

		// place the ball on the paddle
		
		x = paddle.x + paddle.get_width() / 2.0;
			
		y = paddle.y - height - 1;

		index = ball_type;
	}

	// this collision detection function treats the ball as a circle

	bool collids(double& xp, double& yp, double xb, double yb, int widthb, int heightb) const
	{
		return circle_aabb_collision(xp, yp, x, y, get_width() / 2.0, xb, yb, widthb, heightb);
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