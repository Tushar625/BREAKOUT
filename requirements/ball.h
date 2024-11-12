#pragma once

class ball_class
{
	sf::Sound snd;

public:

	/*
		we keep these parameters public so that they can be changed
		later to create different effects
	*/

	double x, y, dx, dy;

	int color;

	ball_class()
	{
		x = y = dx = dy = 0;

		color = 0;
	}

	int get_width() const
	{
		return 8;
	}

	int get_height() const
	{
		return 8;
	}

	void reset(double xin, double yin, int ball_type = 0)
	{
		dx = (100 + rand() % 51) * (rand() % 2 ? -1 : 1);
		
		dy = -(100 + rand() % 51) - ball_type * 10;

		x = xin;

		y = yin;

		color = ball_type;
	}

	// this collision detection function treats the ball as a circle

	bool collids(double& xp, double& yp, const sf::FloatRect& box) const
	{
		return bb::circle_aabb_collision(xp, yp, x + get_width() / 2.0, y + get_width() / 2.0, get_width() / 2.0, box.getPosition().x, box.getPosition().y, box.width, box.height);
	}

	bool collids(double& xp, double& yp, const paddle_class& paddle) const
	{
		return bb::circle_aabb_collision(xp, yp, x + get_width() / 2.0, y + get_width() / 2.0, get_width() / 2.0, paddle.x, paddle.y, paddle.get_width(), paddle.get_height());
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

		if (x + get_width() > VIRTUAL_WIDTH)
		{
			x = VIRTUAL_WIDTH - get_width();

			dx = -dx;

			snd.setBuffer(sound_buffer[WALL_HIT]);

			snd.play();
		}
	}

	void render()
	{
		auto& ball = sprite[BALL][color];

		ball.setPosition(sf::Vector2f(x, y));

		bb::WINDOW.draw(ball);
	}
};